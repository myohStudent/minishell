/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:50:45 by myoh              #+#    #+#             */
/*   Updated: 2020/12/17 23:02:29 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

int		arr_len(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

char	*parse_space(char *s, char *space)
{
	int	i;

	i = 0;
	if (!space || !s)
		return (NULL);
	while (ft_strchr(s, space && s[i] != '\0'))
	{
		s++;
		i++;
	}
	i = ft_strlen(s);
	while (ft_strchr(space, s[i]) && s != 0)
		i--;
	return (ft_substr(s, 0, i + 1));
}

int	check_token(t_minishell *minishell, t_cmd *curr)
{
	char	*temp;
	char	*input;
	int		i;

	pipe_num = 0;
	minishell->redir_num = 0;
	temp = ft_strjoin(curr->command, " ");
	if (curr->option)
		input = ft_strjoin(temp, curr->option);
	else
		input = ft_strdup(temp);
	free(temp);
	i = 0;
	if (!input)
		return (1);
	if (!(ft_strcmp(input, "|||")))
	{
		ft_printf("syntax error near unexpected token `|'\n");
		free(input);
		return (-1);
	}
	if (!(ft_strcmp(input, ">>>")))
	{
		ft_printf("syntax error near unexpected token `>'\n");
		free(input);
		return (-1);
	}
	if (!(ft_strcmp(input, ">>")))
	{
		minishell->redir_num++;
		i += 2;
	}
	while (input[i])
	{
		if (input[i] == '|')
			pipe_num++;
		else if (input[i] == '>' || input[i] == '<')
			minishell->redir_num++;
		i++;
	}
	if (input)
		free(input);
	return (1);
}