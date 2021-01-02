/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:35:27 by seohchoi          #+#    #+#             */
/*   Updated: 2021/01/02 17:55:54 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		dollor_question()
{
	ft_putstr_fd(ft_itoa(g_command_nb), 1);
	ft_putstr_fd(": command not found\n", 1);
	g_command_nb = 127;
	return (1);
}

int		dollar_exec(t_cmd *curr, t_minishell *minishell)
{
	t_env *env;
	int i;
	int j;
	char	*temp;
	t_cmd *envcmd;
	int hasargc = 0;

	env = minishell->env_list;
	i = 0;
	if ((curr->hasquote == 1 && curr->hasenv == 0) || curr->quote_type == 1 )
		return (0);
	while (curr->command[i] != '$' && curr->command[i])
		i++;
	if (!curr->command[i])
		return (0);
	if (curr->command[i] == '$' && curr->command[i + 1] == '?')
		dollor_question();
	else if (curr->command[i] == '$')
	{
		j = 0;
		while (env && j < minishell->env_currnb)
		{
			if (ft_strncmp(env->variable, curr->command + i + 1, ft_strlen(curr->command) - i - 1) == 0)
			{
				envcmd = (t_cmd *)malloc(sizeof(t_cmd));
				if (i != 0)
					envcmd->command = ft_strjoin(ft_substr(curr->command, 0, i), env->value);
				else 
					envcmd->command = ft_strdup(env->value);
				envcmd->argc = 1;
				hasargc = envcmd->argc;
				exec_else(minishell, envcmd);
				free(envcmd);
				return (1);
			}
			j++;
			env = env->next;
		}
		if (!hasargc)
		{
			envcmd = (t_cmd *)malloc(sizeof(t_cmd));
			envcmd->command = ft_substr(curr->command, 0, i);
			exec_else(minishell, envcmd);
			free(envcmd);
			return (1);
		}
		if (curr->option)
		{
			temp = ft_strdup(curr->option);
			free(curr->command);
			free(curr->option);
			curr->option = NULL;
			while (temp[i] && temp[i] != ' ')
				i++;
			if (i == ft_strlen(temp))
				curr->command = ft_strdup(temp);
			else
			{
				curr->command = ft_substr(temp, 0, i);
				while (temp[i])
				{
					if (temp[i] == ' ')
					{
						curr->option = ft_substr(temp, i + 1, ft_strlen(temp));
						break ;
					}
					i++;
				}
			}
			free(temp);
		}
	}
	return (0);
}

int get_next_space(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (i);
		if (ft_isquote(str[i]))
			return (i);
		i++;
	}
	return (-1);
	// if (get_first_quote(str, 2) < get_first_quote(str, 1) || get_first_quote(str, 1) < 0)
	// 	return (get_first_quote(str, 2));
	// else
	// 	return (get_first_quote(str, 1));
}

int		dollar_exec_with_quote(t_cmd *curr, t_minishell *minishell)
{
	t_env *env;
	int i;
	int j;
	int envindex;
	char	*temp;
	char	*startstr;

	i = 0;
	env = minishell->env_list;
	while (curr->command[i] != '$' && curr->command[i])
		i++;
	if (!curr->command[i])
		return (0);
	j = get_next_space(curr->command + i);
	if (curr->command[i] == '$' && curr->command[i + 1] == '?')
		dollor_question();
	else if (curr->command[i] == '$')
	{
		envindex = 0;
		while (env && envindex < minishell->env_currnb)
		{
			// ft_printf(">>>>>>>>>>>%s %d<<<<<<<<<<<\n", curr->command + i + 1, j - 1);
			if (ft_strncmp(env->variable, curr->command + i + 1, j - 1) == 0)
			{

				temp = ft_substr(curr->command, 0, i);
				startstr = ft_strjoin(temp, env->value);
				free(temp);
				temp = ft_substr(curr->command, j + i, ft_strlen(curr->command) - (j + i) );
				free(curr->command);
				curr->command = ft_strjoin(startstr, temp);
				free(startstr);
				free(temp);
				break;
			}
			envindex++;
			env = env->next;
		}
	}
	if (curr->option)
	{
		temp = ft_strdup(curr->option);
		free(curr->command);
		free(curr->option);
		curr->option = NULL;
		while (temp[i] && temp[i] != ' ')
			i++;
		if (i == ft_strlen(temp))
			curr->command = ft_strdup(temp);
		else
		{
			curr->command = ft_substr(temp, 0, i);
			while (temp[i])
			{
				if (temp[i] == ' ')
				{
					curr->option = ft_substr(temp, i + 1, ft_strlen(temp));
					break ;
				}
				i++;
			}
		}
		free(temp);
	}
}