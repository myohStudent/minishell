/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export2(주석본)\.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 14:35:25 by myoh              #+#    #+#             */
/*   Updated: 2020/11/14 20:08:21 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*

char		*get_env(char **env, const char *variable)
{
	int i;
	int cntr;

	i = 0;
	if (env == NULL)
	{
		ft_printf("No Environment\n");
		return (NULL);
	}
	if (variable == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		cntr = 0;
		while (env[i][cntr] && variable[cntr] && env[i][cntr] == variable[cntr])
		{
			if (env[i][cntr + 1] == '\0')
			return ft_strdup("tes");
			if (env[i][cntr + 1] == '=')
				return (ft_strdup(ft_strchr(env[i] + cntr, '=') + 1));
			cntr++;
		}
		i++;
	}
		ft_putendl("---");
	return (NULL);
}

int		is_same(char *s1, char *s2)
{
	int		i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}

//연결리스트를 버블정렬시키는 함수
void	ft_sort(t_list **start, int (*str_cmp)())  //괄호에 값을 넣지 않는다!
{ // str_cmp 변수는 다른 사람들 거 참고했는데 ft_strcmp의 결과값을 함수와 함께 가져오는 것
	t_list	*tmp1;
	t_list	*tmp2;
	t_list	*next;

	tmp1 = *start;
	while (tmp1)
	{
		tmp2 = *start;
		while (tmp2->next)
		{
			if ((*str_cmp)(((t_env *)(tmp2->content))->variable, ((t_env *)(tmp2->next->content))->variable) > 0)
			{ //여기에다 가져온 함수에 원하는 인자를 넣어서 실행한다. ft_strcmp와 동일한 형태로 생각하고 결과값은 int가 된다.
				next = tmp2->content;
				tmp2->content = tmp2->next->content;
				tmp2->next->content = next;
			}
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

//하고 연결리스트용 함수 env_export_print 만들기 ->
void	env_export_print(t_list *start_lst)
{
	int		i;

	i = 0;
	if (!start_lst)
		return ;
	while (start_lst && i < g_env_max)
	{
		if (((t_env *)(start_lst->content))->value)
				ft_printf("declare -x %s=\"%s\"\n",
				((t_env *)(start_lst->content))->variable, ((t_env *)(start_lst->content))->value);
			else if (!((t_env *)(start_lst->content))->value)
				ft_printf("declare -x %s\n",
					((t_env *)(start_lst->content))->variable);
		i++;
	}
	start_lst = start_lst->next;
}#include "../minishell.h"
/*
void	voidfn(void *cmd)
{
	(void)cmd;
}

void	export_basic(t_minishell *minishell)
{
	int 	i;
	t_list	*tmp;

	i = 0;
	tmp = minishell->env_list;
	while (tmp != NULL && i < g_env_max)
	{
		ft_lstadd_back(&minishell->env_list, ft_lstnew(tmp->content));
		//ft_printf("tmp->variable : %s\n", ((t_env *)(tmp->content))->variable);
		tmp = tmp->next;
		i++;
	}
	//ft_sort(&minishell->env_list, ft_strcmp);
	//env_export_print(minishell->env_list);
	//ft_lstclear(&minishell->env_list, voidfn);
	ft_printf("????  ");
}

int			    ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void    		cpy_env(t_minishell *minishell, int j)
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
		//ft_printf("%d ", i);
	}
}

static void     sort_export(t_minishell *minishell, int j)
{
	int i;
	int c;
	char *temp;
	int k;
	char *str;

	c = 0;
	/*
		{

   		for (i = 0; i < n-1; i++)
       // Last i elements are already in place
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);


	i = 0;
	/*if ()
		str = ft_split(curr->option, "=");

	while (i < j - 1 && minishell->export_set[i])
	{
		k = 0;
		while (k < j - i - 1 && minishell->export_set[k + 1])
		{
			if (ft_strcmp(minishell->export_set[k], minishell->export_set[k + 1]) > 0)
			{
				ft_printf("%d ", k);
				temp = minishell->export_set[k];
				minishell->export_set[k] = minishell->export_set[k + 1];
				//free(minishell->export_set[k + 1]);
				minishell->export_set[k + 1] = temp;
			}
			k++;
		}
		i++;
	}
	while (minishell->export_set[i])
		i++;
	minishell->env_currnb = i;
	ft_printf("현재 currnb 개수: (%d) ", minishell->env_currnb);
	ft_printf("---sort끝남---\n");
}

char	**arr_realloc(t_minishell *minishell, char *line)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (arr_len(minishell->export_set) + 2));
	while (minishell->export_set[i] != NULL)
	{
		res[i] = ft_strdup(minishell->export_set[i]);
		i++;
	}
	ft_printf("(%d)",i);
	res[i] = ft_strdup(line);
	res[i + 1] = NULL;
	ft_printf("(%d)\n", i);
	free_arr(minishell->export_set);
	minishell->env_currnb = i + 1; // 넘버 추가
	return (res);
}

int             cmd_export(t_cmd *curr, t_minishell *minishell)
{
	int j;
	int i;
	int unseenfl;
	char    **str;

	i = 0;
	unseenfl = 0;
	j = 0;
	//cpy_env(minishell, minishell->env_nb);
	ft_printf("----요기---\n");

	if (curr->argc == 1)
	{

		export_basic(minishell);
		//ft_printf("현재 export 갯수 : %d\n",arr_len(minishell->export_set));
		//sort_export(minishell, minishell->env_nb);
		/*while (minishell->export_set[i] && i < arr_len(minishell->export_set))
		{
			ft_printf("declare -x %d ", i);
			ft_printf("%s\n", minishell->export_set[i]);
			i++;
		}
		ft_printf("수고하셨습니다\n");
		return (1);
	}

	if (curr->argc == 2 && curr->option != NULL)
	{
		if ((ft_strchr(curr->option,'=') != 0)) // 예외처리
		{
			ft_printf("----if 진입--\n");
			while (curr->option[j] && curr->option[j] != '=')
				j++;
			ft_printf("(%d, %d, %d)\n",j, i, unseenfl);
			while (minishell->export_set[i] != NULL && i < minishell->env_currnb)
			{
				ft_printf("%s\n",minishell->export_set[i]);
				if (ft_strncmp(minishell->export_set[i], curr->option, j + 1) == 0)
				{
					ft_printf("----if 진입--\n");
					minishell->export_set[i] = ft_strdup(curr->option);
					unseenfl = 1;
					break ;
				}
				i++;
				ft_printf("(%d)",i);
			}
		ft_printf("----uneenfl=0 바로 전---\n");
			if (unseenfl == 0)
			{
				ft_printf("(%d)\n",j);
				if (!(minishell->export_set = arr_realloc(minishell, curr->option)))
					return (0);
			}
		}
	}
	return (1);
}*/