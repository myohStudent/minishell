/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:50:45 by myoh              #+#    #+#             */
/*   Updated: 2020/11/23 19:26:18 by myoh             ###   ########.fr       */
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

int	check_separator(t_minishell *minishell, t_cmd *curr)
{
	char	*temp;
	int		i;

	token = NULL;
	minishell->pipe_num = 0;
	minishell->redir_num = 0;
	temp = ft_strdup(curr->option);
	i = 0;
	if (!(ft_strcmp(temp, "|||")))
	{
		ft_printf("syntax error near unexpected token `|'\n");
		free(temp);
		return (-1);
	}
	if (!(ft_strcmp(temp, ">>>")))
	{
		ft_printf("syntax error near unexpected token `>'\n");
		free(temp);
		return (-1);
	}
	if (!(ft_strcmp(temp, ">>")))
	{
		minishell->redir_num++;
		free(temp);
		i += 2;
		return (1);
	}
	while (temp[i])
	{
		if (temp[i] == '|')
		{
			minishell->pipe_num++;
			token = strdup("|");
			free(temp);
			return (1);
		}
		else if (temp[i] == '>' || temp[i] == '<')
		{	
			minishell->redir_num++;
			if (temp[i] == '>')
			{
				if (temp[i] == '>' && temp[i + 1 ]== '>')
					token = strdup(">>");
				token = strdup(">");
			}
			else
				token = strdup("<");
			free(temp);
			return (1);
		}
		i++;
	}

	free(temp);
	return (1);
}

/*void	init_curr(t_cmd *curr)
{
	minishell->pipe_num = 0;
	curr->redir = 0;
	curr->dollar = 0;
	curr->dredir = 0;
}*/