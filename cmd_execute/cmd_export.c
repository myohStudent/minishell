/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 23:12:29 by myoh              #+#    #+#             */
/*   Updated: 2020/10/08 18:03:56 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			    ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
} 

static void     enter_the_dragon(t_minishell *minishell)
{
    int         i;
    int         c;
    int         j;

    i = 0;
    c = 0;
    j = arr_len(minishell->env_set);
    minishell->env.variable = (char **)ft_memalloc(sizeof(char *) * (j / 2 + 1));
    minishell->env.value = (char **)ft_memalloc(sizeof(char *) * (j / 2 + 1));
    while (minishell->env_set[i]) 
    {
        minishell->env.variable[c] = ft_strjoin("", "");
        minishell->env.variable[c] = ft_strdup(minishell->env_set[i]);
        minishell->env.value[c] = ft_strjoin("", "");
        minishell->env.value[c] = ft_strdup(minishell->env_set[i + 1]);
        i++;
        i++;
        c++;
    }
    minishell->env.nb = c;
}

static void     bubble_bubble(t_minishell *minishell)
{
    int i;
    int j;
    int c;
    char *temp;
    int k;

    i = 0;
    c = 0;
    j = arr_len(minishell->env_set);
    enter_the_dragon(minishell);
    ft_printf("j : %d\n", j);
    i = (j / 2) - 1;
    while (i >= 0 && i < (j / 2) && minishell->env.variable[i])
    {
        k = 0;
        while (k < (j / 2) && minishell->env.variable[k + 1])
        {
            if (ft_strcmp(minishell->env.variable[k], minishell->env.variable[k + 1]) > 0)
            {
                temp = ft_strdup(minishell->env.variable[k]);
                minishell->env.variable[k] = ft_strdup(minishell->env.variable[k + 1]);
                minishell->env.variable[k + 1] = temp;
                temp = ft_strdup(minishell->env.value[k]);
                minishell->env.value[k] = ft_strdup(minishell->env.value[k + 1]);
                minishell->env.value[k + 1] = temp;
            }
            k++;
        }
        i--;
  
    }
    free(temp);
}

int             cmd_export(t_cmd *curr, t_minishell *minishell)
{
    int i;
    int e;
    int j;
    int is_added;
    char    **str;

    i = 0;
    e = 0;
    is_added = 0;
    if (curr->argc == 1)
    {
        bubble_bubble(minishell);
        while (minishell->env.variable[i] != NULL)
	    {
            ft_printf("declare -x %d ", i);
		    ft_printf("%s=%s\n", minishell->env.variable[i], minishell->env.value[i]);
		    i++;
	    }
	    ft_printf("\n");
        return (1);
    }
    if (curr->argc == 2 && curr->option != NULL)
    {
		ft_printf("- %s\n",curr->option);
        if (!(str = ft_split(curr->option, '=')))
            return (0);
        ft_printf("[%s]\n %s, %s \n", curr->option, str[0], str[1]);
        while (minishell->env_set[i])
        {
			
            if ((ft_strcmp(str[0], minishell->env_set[i]) == 0) && (minishell->env_set[i + 1] != NULL))
            {
                minishell->env_set[i + 1] = NULL;
                j = 0;
                minishell->env_set[i + 1] = ft_strdup(str[1]);
                ft_printf("(%s| %d)\n",minishell->env_set[i + 1], j);
                e = 1; 
            }
            i++;
        }
        str[0] = NULL;
        str[1] = NULL;
        if (e == 0)
        {
            ft_printf("sss ");
            i = arr_len(minishell->env.variable);
            if (!(str = ft_split(curr->option, '=')))
                return (0);
            enter_the_dragon(minishell);
            minishell->env.variable[minishell->env.nb] = ft_strdup(str[0]);
            minishell->env.value[minishell->env.nb] = ft_strdup(str[1]);
            str[0] = NULL;
            str[1] = NULL;
            is_added = 1;
            ft_printf("minishell->env.variable[%d] = %s, %s\n", minishell->env.nb, minishell->env.variable[i], minishell->env.value[i]);
            minishell->env.nb++;
        }
    }
    free(str[0]);
    free(str[1]);
    return (1);
}