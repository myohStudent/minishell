/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 12:26:13 by myoh              #+#    #+#             */
/*   Updated: 2020/09/18 17:33:41 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./libft/libft.h"
#include "./minishell.h"

/* 프롬프트 만들고 pwd부터 구현하기
현재 디렉토리 구하는 함수: getcwd (unistd에 있다)*/

void	display_prompt(void)
{
	char	buf[4096]; /*얼마를 넣어야 하나?*/
	char	*cwd; /*경로 */
	cwd = getcwd(buf, 4096);
	printf("%s ", cwd);
	printf(" > ");
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		display_prompt();
		signal(SIGINT, sig_handler);
	}
}

void		get_input(t_minishell *minishell)
{
	int		ret;
	int		i;
	int		count;
	char		buf[2];
	char	*cwd;

	buf[0] = ' ';
	buf[1] = '\0';
	free(minishell->input);
	minishell->input = ft_strdup("");
	while(buf[0] != '\n')
	{
		read(STDIN_FILENO, buf, 1);
		//minishell->input = 
		if (buf[0] != '\n')
			minishell->input = ft_strjoin(minishell->input,buf);
	}
	printf("\n 너는 뭔가를 입력했지...$ > %s\n",minishell->input);
	if ((ft_strncmp(minishell->input, "pwd", 3)) == 0)
		printf("%s\n", getcwd(minishell->path, 4096));
	exit(1);
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
	t_minishell	minishell;

	welcome_shell();
	minishell.path = getcwd(NULL, 0);
	while (1)
	{
		display_prompt(); //스탠다드 인풋이 먼저 떠서 프롬프트가 안나와여ㅠㅠㅠ
		signal(SIGINT, sig_handler); //Ctrl + D를 누르면 종료된다!
		get_input(&minishell); // stdin 입력을 input에 저장한다. 
		if (*(minishell.input) != '\n')
			break ;
	}
	return (0);
}