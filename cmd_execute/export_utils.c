/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 22:49:00 by myoh              #+#    #+#             */
/*   Updated: 2020/11/10 17:18:24 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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
}