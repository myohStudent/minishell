/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 10:21:33 by myoh              #+#    #+#             */
/*   Updated: 2021/01/08 04:14:10 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		init_num(t_minishell *minishell)
{
	g_pipe_num = 0;
	minishell->redir_num = 0;
}

int			check_last_token(char *input)
{
	char	*s;

	s = ft_trim(input);
	if (s[ft_strlen(s) - 1] == '|' || s[ft_strlen(s) - 1] == '>'
		|| s[ft_strlen(s) - 1] == '<')
	{
		ft_printf("올바르게 다시 입력하세요\n");
		free_command(s);
		return (-1);
	}
	free(g_input);
	g_input = NULL;
	g_input = ft_strdup(s);
	free(input);
	input = NULL;
	input = ft_strdup(s);
	free(s);
	s = NULL;
	return (1);
}

int			check_token(t_minishell *minishell, t_cmd *curr)
{
	char	*input;
	int		i;

	init_num(minishell);
	input = ft_strdup(g_input);
	i = 0;
	if (exceptions(input) < 0 || check_last_token(input) < 0)
	{
		free(input);
		return (0);
	}
	while (input[i])
	{
		if (input[i] == '|')
			g_pipe_num++;
		else if (input[i] == '>' || input[i] == '<')
			minishell->redir_num++;
		i++;
	}
	free_command(input);
	return (1);
}

void		free_globals(void)
{
	if (g_input)
	{
		free(g_input);
		g_input = NULL;
	}
}

void		clear_scmd(t_cmd *curr, t_minishell *minishell)
{
	t_cmd		*next;

	while (curr != NULL)
	{
		if (curr->command != NULL)
		{
			free(curr->command);
			curr->command = NULL;
		}
		if (curr->option != NULL)
		{
			free(curr->option);
			curr->option = NULL;
		}
		if (curr->type)
			curr->type = 0;
		curr->fd = 0;
		curr->argc = 0;
		next = curr->next;
		free(curr);
		curr = next;
	}
}
