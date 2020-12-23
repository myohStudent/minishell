/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 11:04:26 by myoh              #+#    #+#             */
/*   Updated: 2020/12/23 17:11:35 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			get_cd_export(t_cmd *new)
{
	if (ft_compare(new->command, "cd"))
	{
        if (ft_compare(new->option, "") && new->type < 3 && new->type != LASTPIPE)
			new->argc = 1;
	}
	if (ft_compare(new->command, "export"))
	{
		if (new->type == LASTPIPE)
		{
			if (new->option == NULL)
			 	new->argc = 1; 
			else
				new->argc = 42;
		}
		else if (new->type > 3)
		{
            if (new->option != NULL)
                new->argc = 2;
            else
                new->argc = 1;
		}
    }
}

void			get_cmd_argc(t_cmd *new)
{
	get_cd_export(new);
    if (ft_compare(new->command, "unset"))
    {
        if (new->type == LASTPIPE)
            new->argc = 42;
        else if (new->type > 3)
            new->argc = 2;
    }
    if (ft_compare(new->command, "exit"))
    {
        if (new->type == LASTPIPE)
            ;
        else if (new->type > 3)
            new->argc = 1;
    }
}

char			*split_cmd(char *s)
{
	int			i;
	char		*str;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	str = malloc(sizeof(char) * i);
	str = ft_substr(s, 0, i);
	str[i] = '\0';
	return (str); 
}

char			*split_opt(char *s)
{
	int			i;
	char		*str;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	str = malloc(sizeof(char) * (ft_strlen(s) - i));
	str = ft_substr(s, i + 1, ft_strlen(s));
	return (str); 
}

t_cmd			*add_next_node(t_cmd *target, char *s, int i)
{
	t_cmd		*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
    new->next = target->next;
	new->command = ft_strdup(split_cmd(s));
	new->option = ft_strdup(split_opt(s));
	if (ft_compare(new->option, ""))
	{
		free(new->option);
		new->option = NULL;
	}
	new->type = i;
	if (ft_compare(new->command, "export") || ft_compare(new->command, "unset")
	|| ft_compare(new->command, "cd") || ft_compare(new->command, "exit"))
		get_cmd_argc(new);
	new->fd = 0;
	//ft_printf("cmd:/%s/ opt:/%s/ argc:/%d/\n",new->command, new->option, new->argc);
	target->next = new;
	return (target);
}
