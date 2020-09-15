/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 12:26:13 by myoh              #+#    #+#             */
/*   Updated: 2020/09/15 17:43:09 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./libft/libft.h"
#include "./minishell.h"

/* 프롬프트 만들고 pwd부터 구현하기
현재 디렉토리 구하는 함수: getcwd (unistd에 있다)*/

void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size)
{
	void	*new;

	if (!ptr)
		return (NULL);
	if (!(new = ft_memalloc(new_size)))
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new, ptr, prev_size < new_size ? prev_size : new_size);
	free(ptr);
	return (new);
}

void	display_prompt(void)
{
	char	buf[4096]; /*얼마를 넣어야 하나?*/
	char	*cwd; /*경로 */
	cwd = getcwd(buf, 4096);
	printf("%s > ", cwd);
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

static void		get_input(char **input)
{
	int		ret;
	char	buf;
	int		i;
	int		count;

	*input = ft_strnew(1);
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
	}
	/*if ((ft_strchr(*input, '$') != NULL) || (ft_strchr(*input, '~') != NULL))
		*input = parse_input(*input);*/
}

int		main(int ac, char **av, char **env)
{
	char *input;
	char **shell_env;
	welcome_shell();

	while (1)
	{
		input = NULL;
		//shell_env = initenv(ac, av, env);
		display_prompt(); //스탠다드 인풋이 먼저 떠서 프롬프트가 안나와여ㅠㅠㅠ
		signal(SIGINT, sig_handler); //Ctrl + D를 누르면 종료된다!
		get_input(&input);
		//get_next_line(0, &input);
		//read(0, input, 255);
		//fgets(input, 255, stdin); 
		if (*input == '\n')
			break ;
	}
	return (0);
}