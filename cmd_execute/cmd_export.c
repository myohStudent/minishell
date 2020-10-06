/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 23:12:29 by myoh              #+#    #+#             */
/*   Updated: 2020/10/06 19:28:55 by myoh             ###   ########.fr       */
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

void    bubble_bubble(t_minishell *minishell)
{
    int i;
    int j;
    int c;
    char *temp;

    i = 0;
    c = 0;
    j = arr_len(minishell->env_set);
    minishell->env.variable = (char **)ft_memalloc(sizeof(char *) * (j / 2 + 1));
    minishell->env.value = (char **)ft_memalloc(sizeof(char *) * (j / 2 + 1));
    while (minishell->env_set[i]) 
    {
        //minishell->env->variable[c] = ft_strjoin("", "");
        minishell->env.variable[c] = ft_strdup(minishell->env_set[i]);
        //minishell->env->value[c] = ft_strjoin("", "");
        minishell->env.value[c] = ft_strdup(minishell->env_set[i + 1]);
        i++;
        i++;
        c++;
    }
    ft_printf("center: %d\n, c: %d", i / 2, c);
    i = 0;
    for (i = 0; i < j ; i++)
        {
            for(int k = 0; k < (c / 2) - i - 1 ; k++)
            {
                if (ft_strcmp(minishell->env.variable[k], minishell->env.variable[k + 1]) > 0)
                {
                    temp = ft_strdup(minishell->env.variable[k]);
                    minishell->env.variable[k] = ft_strdup(minishell->env.variable[k + 1]);
                    minishell->env.variable[k + 1] = temp;
                    free(temp);
                    temp = ft_strdup(minishell->env.value[k]);
                    minishell->env.value[k] = ft_strdup(minishell->env.value[k + 1]);
                    minishell->env.value[k + 1] = temp;
                    free(temp);
                }
            }
        }
    /*while (dst[i] && !(i % 2))
    {
        if ((dst[i + 2]) && ft_strcmp(dst[i], dst[i + 2]) > 0)
        {
            temp = ft_strdup(dst[i]);
            dst[i] = ft_strdup(dst[i + 2]);
            dst[i + 2] = temp;
            free(temp);
            temp = ft_strdup(dst[i + 1]);
            dst[i + 1] = ft_strdup(dst[i + 3]);
            dst[i + 3] = temp;
            free(temp);
        }
        else if (dst[i + 2] == NULL)
            break;
        i++;
        i++;    
    }   */
}

int    cmd_export(t_cmd *curr, t_minishell *minishell)
{
    int i;
    int e;
    int j;

    char    **str;

    i = 0;
    e = 0;
   
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
                //free(minishell->env_set[i + 1]);
                //minishell->env_set[i + 1] = ft_strjoin("", "");
                minishell->env_set[i + 1] = NULL;
                j = 0;
                minishell->env_set[i + 1] = ft_strdup(str[1]);
                ft_printf("(%s| %d)\n",minishell->env_set[i + 1], j);
                e = 1;
            }
            i++;
        }
        if (e == 0)
        {
            ft_printf("you can add a variable and a corresponding value.\n");
            
            /*
            minishell->env_set[i] = ft_strjoin("", "");
            
            minishell->env_set[i] = strjoin(minishell->env_set[i], str[0])
            minishell->env_set[i] = strjoin(minishell->env_set[i], str[1]);
            */
        }
    }
    free(str[0]);
    free(str[1]);
    return (1);
}
