/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exec_with_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:19:56 by seohchoi          #+#    #+#             */
/*   Updated: 2021/01/04 20:31:52 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			get_next_space(char *str)
{
	int		i;

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
}

int			quote_dollar_strjoin(t_cmd *curr, t_minishell *minishell, \
int i, char *value)
{
	char	*temp;
	char	*startstr;
	int		j;

	j = get_next_space(curr->command + i);
	temp = ft_substr(curr->command, 0, i);
	startstr = ft_strjoin(temp, value);
	free(temp);
	temp = ft_substr(curr->command, j + i,\
	ft_strlen(curr->command) - (j + i));
	free(curr->command);
	curr->command = ft_strjoin(startstr, temp);
	free(startstr);
	free(temp);
	if (ft_strsearch(curr->command + i + 1, '$') > -1)
		dollar_exec_with_quote(curr, minishell);
	return (1);
}

int			dollar_exec_with_quote(t_cmd *curr,\
t_minishell *minishell)
{
	t_env	*env;
	int		i;
	int		j;
	int		envindex;

	env = minishell->env_list;
	i = ft_strsearch(curr->command, '$');
	if (i < 0)
		return (0);
	j = get_next_space(curr->command + i);
	if (curr->command[i] == '$' && curr->command[i + 1] == '?')
		dollar_question();
	envindex = 0;
	while (env && envindex < minishell->env_currnb)
	{
		if (ft_strncmp(env->variable, curr->command + i + 1, j - 1) == 0)
			return (quote_dollar_strjoin(curr, minishell, i, env->value));
		envindex++;
		env = env->next;
	}
	return (0);
}
