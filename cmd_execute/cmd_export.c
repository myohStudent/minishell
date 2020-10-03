/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 23:12:29 by myoh              #+#    #+#             */
/*   Updated: 2020/10/03 17:23:45 by myoh             ###   ########.fr       */
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

char    *bubble_bubble(char *src)
{
    int i;
    int j;
    char *temp;
    char    **dst;

    i = 0;
    j = arr_len(src);
    printf("minishell->set_env length : %d\n", j);
    dst = (char *)malloc(sizeof(char) * j);
    while (i < j)
    {
        temp[i] = ft_strdup(src[i]);

        i++;
    }
    i = 0;
    while (dst[i] && (i / 2) != 0 && i < j)
    {
        //if (ft_strcmp(src[i], src[i + 2]) == 0)

        if (ft_strcmp(dst[i], dst[i + 2]) < 0)
        {
            temp = ft_strdup(dst[i]);
            dst[i] = ft_strdup(dst[i + 2]);
            dst[i + 2] = temp;

            temp = ft_strdup(dst[i + 1]);
            dst[i + 1] = ft_strdup(dst[i + 3]);
            dst[i + 3] = temp;
            free(temp);
        }
        i++;
        i++;    
    }   
    return (dst);
}

void    cmd_export(t_cmd *curr, t_minishell *minishell)
{
    int i;
    int e;
    int j;

    char    **str;
    char    **temp;

    i = 0;
    e = 0;
    if (!(temp = (char **)malloc(sizeof(char) * (arr_len(minishell->env_set)))))
        return ;
    if (curr->argc == 1)
    {
        temp = bubble_bubble(minishell->env_set);
        while (minishell->env_set[i] != NULL)
	    {
            ft_printf("declare -x ");
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
			
            if ((ft_strcmp(str[0], minishell->env_set[i]) == 0) && (minishell->env_set[i + 1] != NULL))
            {
                //free(minishell->env_set[i + 1]);
                minishell->env_set[i + 1] = ft_strjoin("", "");
                j = 0;
                minishell->env_set[i + 1] = ft_strdup(str[1]);
                /*while (minishell->env_set[i + 1] && str[1][j])
                {
                    minishell->env_set[i + 1][j] = str[1][j];
                    j++;
                }*/
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
}
