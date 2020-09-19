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

void get_input(t_minishell *minishell)
{
	char buf[2];
	char *input;

	minishell->input.argc = 0;
	buf[0] = ' ';
	buf[1] = '\0';
	input = ft_strdup("");
	while (buf[0] != '\n')
	{
		read(STDIN_FILENO, buf, 1);
		if (buf[0] != '\n')
			input = ft_strjoin(input, buf);
	}
	//할일 : parse_input에서 ; 별로 명령어 나누는 처리 해줘야함(linked list 사용해야할듯)
	//할일 : 라인 끝자락에 공백이 들어갔을 경우 argc 추가하지않기.
	parse_input(minishell, input);
	//할일 : 이하 내용을 담을 함수 만들기, 함수는 ; 개수만큼 루프 돌도록
	if (!(ft_strncmp(minishell->input.argv[0], "pwd", 3)))
	{
		if (minishell->input.argc == 1)
			printf("%s\n", getcwd(minishell->path, 4096));
		else
			printf("pwd: too many arguments\n");
	}
	//할일(나중에) : 명령어별로 함수 분할하기
	else if (!(ft_strncmp(minishell->input.argv[0], "cd", 2)))
	{
		if (minishell->input.argc == 1)
			chdir("~"); //환경변수가 없어서 작동을 안합니다.
		else if (minishell->input.argc == 2)
		{
			if (chdir(minishell->input.argv[1]) < 0) //경로가 실제 존재하는지 체크합니다.
				printf("cd: no such file or directory\n");
		}
		else if (minishell->input.argc > 2)
			printf("cd: too many arguments\n");
	}
	//할일 : free함수를 만들기.
	for (int i = 0; minishell->input.argv[i]; i++)
		free(minishell->input.argv[i]);
	//exit(1);
	/**input = ft_strnew(1);
	count = 1;
	i = 0;
	while ((ret = read(0, &buf, 1)) && buf != '\n')
	{
		*(*input + i++) = buf;
		*input = ft_realloc(*input, count, count + 1);
		count++;
	}
	*(*input + i) = '\0';
	if (!ret)
	{
		free(*input);
		ft_exit(input);
	}*/
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
		signal(SIGINT, &ctrlc_handler);  //Ctrl + C를 누르면 종료된다?
		signal(SIGQUIT, &ctrld_handler); //Ctrl + \를 누르면 종료된다?
		get_input(&minishell);		  // stdin 입력을 input에 저장한다.
		/*if (*(minishell.input) != '\n')
			break;*/
	}
	return (0);
}