/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 21:20:24 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 21:22:30 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_remove_quote(t_cmd *curr)
{
	char	*temp;
	int		quotenum;
	int		i;

	quotenum = 0;
	i = 0;
	while (curr->command[i])
	{
		if (ft_isquote(curr->command[i]))
			quotenum++;
		i++;
	}
	if (curr->quote_type > 0)
	{
		if (curr->quote_type == 1)
			temp = ft_trimchar(curr->command, '\'');
		if (curr->quote_type == 2)
			temp = ft_trimchar(curr->command, '\"');
		free(curr->command);
		curr->command = ft_strdup(temp);
	}
	if (curr->quote_type == 0)
	{
		temp = ft_trimchar(curr->command, '\"');
		free(curr->command);
		curr->command = ft_trimchar(temp, '\'');
		free(temp);
	}
	if (quotenum > 2)
		quotenum = 2;
	return (quotenum);
}

void		split_argv_quotes_cmd(t_cmd *curr)
{
	int		i;
	char	*temp;
	int		len;
	int		lastquote;
	int		d;
	int		j;

	i = 0;
	curr->option = NULL;
	if ((!curr || !curr->command) && !curr->hasquote)
		return ;
	lastquote = get_first_quote(curr->command + 1, curr->quote_type);
	d = has_quotes(curr);
	j = ft_remove_quote(curr);
	i = d - j;
	if (curr->quote_type == 2 || curr->quote_type == 1)
		i = lastquote;
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
