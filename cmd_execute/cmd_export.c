/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 23:12:29 by myoh              #+#    #+#             */
/*   Updated: 2020/10/02 22:02:21 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void    cmd_export(t_cmd *curr, t_minishell *minishell)
{
    int i;
    int e;

    char    **str;

    i = 0;
    e = 0;
    if (curr->argc == 1)
    {
        while (minishell->env_set[i] != NULL)
	    {
		    ft_printf("%s=%s\n", minishell->env_set[i], minishell->env_set[i+1]);
		    i++;
	    	i++;
	    }
	    ft_printf("\n");
        return ;
    }
    if (curr->argc == 2 && curr->option != NULL)
    {
		ft_printf("- %s\n",curr->option);
        if (!(str = ft_split(curr->option, '=')))
            return ;
        ft_printf("[%s]\n %s, %s \n", curr->option, str[0], str[1]);
        while (minishell->env_set[i])
        {
            if ((ft_strcmp(str[0], minishell->env_set[i]) == 0) && !(minishell->env_set[i + 1]))
            {
                free(minishell->env_set[i + 1]);
                minishell->env_set[i + 1] = ft_strdup(str[0]); 
                e = 1;
            }
            i++;
        }
        
        if (e == 0)
        {
            ft_printf("you've come into the e world\n");
            /*
            minishell->env_set[i] = (char *)malloc(char) * (ft_strlen(str[1]) 
            minishell->env_set[i] = strjoin(minishell->env_set[i], str[0])
            minishell->env_set[i] = strjoin(minishell->env_set[i], str[1]);
            */
        }
    }
    free(str[0]);
    free(str[1]);
}