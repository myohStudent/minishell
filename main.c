/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoichoi <seohchchoioi@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 12:26:13 by myoh              #+#    #+#             */
/*   Updated: 2020/09/19 16:21:15 by seohchchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./libft/libft.h"
#include "./minishell.h"

/* 프롬프트 만들고 pwd부터 구현하기
현재 디렉토리 구하는 함수: getcwd (unistd에 있다)*/

void display_prompt(void)
{
	char buf[4096]; /*얼마를 넣어야 하나?*/
	char *cwd;		/*경로 */
	cwd = getcwd(buf, 4096);
	printf("%s ", cwd);
	printf("> ");
}

int		main(int ac, char **av, char **env)
{
	t_minishell minishell;

	welcome_shell();
	//init_env(env, &minishell);
	minishell.path = getcwd(NULL, 0);
	while (1)
	{
		//display_prompt();			  //스탠다드 인풋이 먼저 떠서 프롬프트가 안나와여ㅠㅠㅠ
		signal(SIGINT, parent_signal_handler); //Ctrl+C Ctrl+D Ctrl+\ 수행하기
		signal(SIGQUIT, parent_signal_handler); //Ctrl+C Ctrl+D Ctrl+\ 수행하기
		//display_prompt();
		printf("minishell >\n \b\b \b\b");
		cmd_handler(&minishell);		  // stdin 입력을 input에 저장한다.
		/*if (*(minishell.input) != '\n')
			break;*/
	}
	return (0);
}