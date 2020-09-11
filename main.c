/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 12:26:13 by myoh              #+#    #+#             */
/*   Updated: 2020/09/11 12:53:06 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "./get_next_line/get_next_line_bonus.h"

#define EXITCMD "exit"

/* 프롬프트 만들고 pwd부터 구현하기
현재 디렉토리 구하는 함수: getcwd (unistd에 있다)*/

static void getinput(char **input)
{
	int ret;
	char buf;

}

void	display_prompt(void)
{
	char	buf[1024]; /*얼마를 넣어야 하나?*/
	char	*cwd; /*경로 */

	cwd = getcwd(buf, 1024);
	printf("cwd >");
}

int		main(int ac, char **av, char **env)
{
	char input[256];
    char *ptr = input;
    char *args[64];
    int wstatus;

	*input = 0;
	*args = 0;
	while (1)
	{
		display_prompt();
		fgets(input, 255, stdin);
		/*signal(SIGINT, sig);*/
		if (*input == '\n')
			continue;
		//getinput
		/*if (ft_isemptystr(input, 1))
		{
			free(input);
			continue ;
		}*/

		/* get_next_line( ); */		
	}
}