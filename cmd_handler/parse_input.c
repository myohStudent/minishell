/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 01:03:31 by seohchoi          #+#    #+#             */
/*   Updated: 2021/01/08 04:08:21 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			get_argc(t_cmd *curr)
{
	int		i;
	int		ac;

	i = 0;
	while (curr->command[i])
	{
		if (ft_isspace(curr->command[i]))
			curr->argc++;
		i++;
	}
	i--;
	while (curr->command[i] && ft_isspace(curr->command[i]))
	{
		curr->argc--;
		i--;
	}
	curr->argc++;
	return (curr->argc);
}

void		split_argv(t_cmd *curr)
{
	int		i;
	char	*temp;
	int		len;

	i = 0;
	curr->option = NULL;
	if (!curr || !curr->command || (get_argc(curr) == 1 && curr->hasquote == 0))
		return ;
	if (ft_isquote(curr->command[0]) && has_quotes(curr) \
	&& curr->command[has_quotes(curr)] != ' ')
		i = has_quotes(curr);
	i -= ft_remove_quote(curr);
	if (i < 0)
		i = 0;
	while (!(ft_isspace(curr->command[i])) && curr->command[i])
		i++;
	len = ft_strlen(curr->command);
	temp = ft_substr(curr->command, 0, i);
	curr->option = ft_substr(curr->command, i + 1, len - (i + 1));
	free(curr->command);
	curr->command = ft_strdup(temp);
	free(temp);
	temp = 0;
}

void		set_node(t_minishell *minishell, t_cmd *new, \
char *data, int word_end)
{
	int		word_start;

	word_start = 0;
	while (ft_isspace(data[word_start]))
		word_start++;
	while (ft_isspace(data[word_end]) || data[word_end] == ';')
		word_end--;
	new->command = ft_substr(data, word_start, word_end - word_start + 1);
	get_quote_type(new);
	if (ft_isquote(new->command[0]) && has_quotes(new))
	{
		new->argc = 0;
		if (new->hasenv == 1 && new->quote_type != 1)
			dollar_exec_with_quote(new, minishell);
		split_argv_quotes_cmd(new);
	}
	else
	{
		if (new->hasenv == 1 && new->quote_type != 1)
			dollar_exec_with_quote(new, minishell);
		split_argv(new);
	}
	if (new->option != NULL && new->option)
		tild_handler(minishell, new);
}

t_cmd		*create_node(t_minishell *minishell, char *data, int word_len)
{
	t_cmd	*new;
	int		i;

	i = 0;
	if (!(new = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	new->argc = 0;
	new->hasquote = 0;
	new->hasenv = 0;
	new->quote_type = 0;
	set_node(minishell, new, data, word_len);
	new->next = 0;
	return (new);
}

int			parse_cmd(t_minishell *minishell, t_cmd *cmd, char *input)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	if (!input)
		return (0);
	while (input[end] && end < ft_strlen(input))
	{
		start = end;
		while (input[end] && input[end] != ';')
			end++;
		if (input[end] == ';' || !input[end])
		{
			cmd->next = create_node(minishell, input + start, end - start - 1);
			ft_printf("argc = %d\n", cmd->argc);
			cmd = cmd->next;
		}
		end++;
	}
	return (1);
}
