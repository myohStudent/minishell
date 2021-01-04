/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:35:27 by seohchoi          #+#    #+#             */
/*   Updated: 2021/01/04 20:22:47 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			dollar_question(void)
{
	ft_putstr_fd(ft_itoa(g_command_nb), 1);
	ft_putstr_fd(": command not found\n", 1);
	g_command_nb = 127;
	return (1);
}

int			ft_strsearch(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	if (str[i] == 0)
		return (-1);
	return (i);
}

int			option_to_command(t_cmd *curr)
{
	char	*temp;
	int		i;

	i = 0;
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
		while (temp[i] && temp[i] != ' ')
			i++;
		if (temp[i] == ' ')
			curr->option = ft_substr(temp, i + 1, ft_strlen(temp));
	}
	free(temp);
	return (0);
}

int			dollar_strjoin(t_cmd *curr, t_minishell *minishell,\
int i, char *value)
{
	t_cmd	*envcmd;

	envcmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (i != 0)
		envcmd->command = ft_strjoin(\
		ft_substr(curr->command, 0, i), value);
	else
		envcmd->command = ft_strdup(value);
	envcmd->argc = 1;
	exec_else(minishell, envcmd);
	free(envcmd);
	return (1);
}

int			dollar_exec(t_cmd *curr, t_minishell *minishell)
{
	t_env	*env;
	int		i;
	int		envindex;

	env = minishell->env_list;
	if ((curr->hasquote == 1 && curr->hasenv == 0) || curr->quote_type == 1)
		return (0);
	i = ft_strsearch(curr->command, '$');
	if (i < 0)
		return (0);
	if (curr->command[i] == '$' && curr->command[i + 1] == '?')
		dollar_question();
	envindex = 0;
	while (env && envindex < minishell->env_currnb)
	{
		if (ft_strncmp(env->variable, curr->command + i + 1, \
		ft_strlen(curr->command) - i - 1) == 0)
			return (dollar_strjoin(curr, minishell, i, env->value));
		envindex++;
		env = env->next;
	}
	if (curr->option)
		return (option_to_command(curr));
	return (0);
}
