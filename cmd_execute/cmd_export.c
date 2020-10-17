/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 23:12:29 by myoh              #+#    #+#             */
/*   Updated: 2020/10/18 00:54:22 by myoh             ###   ########.fr       */
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

static void     cpy_env(t_minishell *minishell, int j)
{
    int         i;
    int         c;

    i = 0;
    c = 0;
    minishell->export_set = (char **)ft_memalloc(sizeof(char *) * (j + 1));
    while (minishell->env_set[i] != NULL)
    {
        minishell->export_set[i] = ft_strdup(minishell->env_set[i]);
        i++;
        ft_printf("%d ", i);
    }
   /* ft_printf("---cpy_env 들어옴--- \n");
   // j = arr_len(minishell->env_set);
    minishell->env.variable = (char **)ft_memalloc(sizeof(char *) * (j / 2 + 1));
    minishell->env.value = (char **)ft_memalloc(sizeof(char *) * (j / 2 + 1));
    ft_printf("(%d)",j/2);
    while (minishell->env_set[i] != NULL && minishell->env_set[i + 1] != NULL && c < j/2)
    {
        //minishell->env.variable[c] = ft_strjoin("", "");
        minishell->env.variable[c] = ft_strdup(minishell->env_set[i]);
	   //minishell->env.value[c] = ft_strjoin("", "");
        minishell->env.value[c] = ft_strdup(minishell->env_set[i + 1]);
        i++;
        i++;
        c++;
        ft_printf("%d",i);
    }
    minishell->env.val_index = c;*/
    ft_printf("cpy_env 나옴\n");
}

static void     sort_export(t_minishell *minishell, int j)
{
    int i;
    int c;
    char *temp;
    int k;

    c = 0;
   // cpy_env(minishell, j);
    ft_printf("j : %d\n", j);
    i = (j / 2) - 1;
    ft_printf("---이것---\n");
    while (i >= 0 && minishell->export_set[i])
    {
        k = 0;
        while (k < (j / 2) && minishell->export_set[k + 1])
        {
            if (ft_strcmp(minishell->export_set[k], minishell->export_set[k + 1]) > 0)
            {
                temp = ft_strdup(minishell->export_set[k]);
                minishell->export_set[k] = ft_strdup(minishell->export_set[k + 1]);
                minishell->export_set[k + 1] = temp;
            }
			k++;
        }
        i--;
    }
   /* while (i >= 0 && minishell->env.variable[i])
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
    }*/
    /*while (minishell->env.variable[k] != NULL)
    {
        minishell->env.variable[k] = ft_strdup()
        k++;
    }*/
    free(temp);
}

int             cmd_export(t_cmd *curr, t_minishell *minishell)
{
    int i;
    int e;
    int j;
    char    **str;

    i = 0;
    e = 0;
    ft_printf("----요기---\n");
	j = arr_len(minishell->env_set);
    cpy_env(minishell, minishell->env_nb);

    if (curr->argc == 1)
    {
        sort_export(minishell, minishell->env_nb);
        while (minishell->export_set[i])
        {
            ft_printf("declare -x %d ", i);
		    ft_printf("%s\n", minishell->export_set[i]);
		    i++;
        }
        ft_printf("\n");
        return (1);
    }
    if (curr->argc == 2 && curr->option != NULL)
    {
        if ((ft_strchr(curr->option,'=') == 0))
        {
			ft_printf("-------chr: %c 리턴됨------\n", ft_strchr(curr->option,'='));
			return (0);
            e = 1;
		}
        if (e == 0)
        {
            
        }
    }
   /* if (curr->argc == 1)
    {
        sort_export(minishell, minishell->env_nb);
        while (minishell->env.variable[i] && minishell->env.variable[i] != NULL)
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
        if ((ft_strchr(curr->option,'=') == 0) || !(str = ft_split(curr->option, '=')))
        {
			ft_printf("-------chr: %c 리턴됨------\n",ft_strchr(curr->option,'='));
			return (0);
		}
		

        ft_printf("[%s]\n %s, %s \n", curr->option, str[0], str[1]);
		ft_printf("-------------\n");

        while (minishell->env_set[i] != NULL)
        {
            ft_printf("%d",i);
            if ((ft_strcmp(str[0], minishell->env_set[i]) == 0) && (minishell->env_set[i + 1] != NULL))
            {
                minishell->env_set[i + 1] = NULL;
                j = 0;
                minishell->env_set[i + 1] = ft_strdup(str[1]);
                ft_printf("(%s| %d)\n",minishell->env_set[i + 1], j);
                e = 1; //기존에 있는 변수였다
            }
            i++;
        }
		ft_printf("-------------\n");

		free(str[0]);
		free(str[1]);
		//
		ft_printf("-------------\n");
        if (e == 0) //기존의 것이 아니다 새로 만들어야 된다
        {
            //minishell->env_currnb = arr_len(minishell->env_set);
            ft_printf("len : %d\n", minishell->env_currnb);
            if (!(str = ft_split(curr->option, '=')) && !(ft_strchr(curr->option, '=')))
                return (0);
            //cpy_env(minishell, j); //env_set에 있는 데이터를 env_varible에 넣기
            //i = arr_len(minishell->env.variable);
            minishell->env.variable[minishell->env.val_index] = ft_strdup(str[0]);
            minishell->env_set[minishell->env_currnb] = ft_strdup(str[0]);
            
			minishell->env.value[minishell->env.val_index] = ft_strdup(str[1]);
            minishell->env_set[minishell->env_currnb + 1] = ft_strdup(str[1]);
            str[0] = NULL;
            str[1] = NULL;
            minishell->env.is_added += 1;
            ft_printf("minishell->env.variable[%d] = %s, %s\n", minishell->env.val_index, minishell->env.variable[minishell->env.val_index], minishell->env.value[minishell->env.val_index]);
            ft_printf("minishell->env.set[%d] = %s, %s\n", minishell->env_currnb, minishell->env_set[minishell->env_currnb], minishell->env_set[minishell->env_currnb+1]);
            
            minishell->env.val_index++;
            minishell->env_currnb++;
            minishell->env_currnb++;
            free(str[0]);
    	    free(str[1]);
        }
	}*/
    return (1);
}