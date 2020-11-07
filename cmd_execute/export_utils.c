/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 22:49:00 by myoh              #+#    #+#             */
/*   Updated: 2020/11/07 23:08:53 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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