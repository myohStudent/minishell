/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 20:39:08 by myoh              #+#    #+#             */
/*   Updated: 2020/10/18 21:19:20 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*modify_argv(char *str, t_list *envs)
{
	char	*ret;

	ret = 0;
	if (has_quote(str))
		ret = parse_quote(str, envs);
	else if (has_env(str))
		ret = parse_env(str, envs);
	free(str);
	return (ret);
}

char	**get_argv(char *line, t_list *envs)
{
	int		i;
	char	**argv;

	if (!(argv = ft_split(line, ' ')))
		return (0);
	i = -1;
	while (argv[++i])
	{
		if ((ft_strlen(argv[i]) != 1)
			&& (has_quote(argv[i]) || has_env(argv[i])))
			argv[i] = modify_argv(argv[i], envs);
	}
	return (argv);
}

void	parse_pipe(char **line, t_pipe *p, t_list *envs)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '|')
		{
			temp = ft_substr(*line, 0, i);
			p->line = ft_strtrim(temp, " ");
			free(temp);
			temp = ft_substr(*line, i + 1, ft_strlen(*line) - i);
			temp2 = ft_strtrim(temp, " ");
			free(temp);
			*line = temp2;
			p->argv = get_argv(p->line, envs); //옵션 나누는 함수 (redirection 포함)
			return ;
		}
	}
}


void	exec_pipe_case_zero(int child, int fd[2], t_list *envs, t_pipe p)
{
	if (child == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_cmds(p.line, envs);
		exit(EXIT_SUCCESS);
	}
}

void	exec_pipe_case_one(int child, int fd[2], t_list *envs, char *line)
{
	if (child == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec_cmds(line, envs); //exec_piped의 상위함수(재귀 비슷)
		exit(EXIT_SUCCESS);
	}
}

void	exec_pipe(char *line, t_list *envs)
{
	int		fd[2];
	int		child[2];
	int		status[2];
	t_pipe	p;

	parse_pipe(&line, &p, envs); 
	//p->line과 p->argv에 ft_strtrim으로 파싱되어 입력된다
	//입력 line을 trim한다.
	pipe(fd);
	//매개변수로 들어온 fd[0]에 read, fd[1]에 write를 할당한다. 파이프의 양 끝을 만든다.
	//성공시 0, 실패시 -1 반환, 서로 독립된 프로세스들이 데이터를 주고받을 수 있도록 만듦
	// 하나의 파이프 및 파이프에 대한 두 개의 파일 디스크립터가 생성
	//파이프 : 한 프로세스의 출력이 다른 프로세스의 입력으로 들어가서 두개의 프로세스가 inter-communication 을 한다.

	child[0] = fork();
	//파이프의 복사본을 만든다. child[0] <- pid 
	//1이상이 부모고 0이 자식

	//부모가 자식으로 부터 자료를 조회하기를 원한다면, fd1를 닫아야 하고 자식은 fd0를 닫아야 한다.
	//부모가 자식에게 자료를 보내고자 한다면, fd0를 닫아야 하고 자식은 fd1을 닫아야 한다.
	//부모와 자식간에 식별자를 공유하고 있으므로, 관계하고 있지 않는 파이프의 끝은 항상 닫혀져야만 한다
	exec_pipe_case_zero(child[0], fd, envs, p);
	if (child[0] == 0) //child[0]이 자식프로세스일경우, 
	{
		dup2(fd[0], STDIN_FILENO); 
		//fd[0]은 read다.
		// 화면에 표시되는 것을 파일로 저장하기 위해(file descriptor로 저장하기 위해) 사용한다.
		//첫 번째 인자로 열려진 파일 디스크립터가 참조하는 파일 테이블 엔트리를 두 번째 전달한 파일 디스크립터도 참조한다.
		close(fd[0]);//열려져있는 양 파이프 (fd)를 닫는다.
		close(fd[1]);
		exec_cmds(line, envs); //exec_piped의 상위함수(재귀 비슷)
		//trim한 line을 상위함수에 넣어서 파이프/리다이렉션/따옴표/달러 그외 순으로 검사한다.
		exit(EXIT_SUCCESS);
	}
	free_double_arr(p.argv);
	free(p.line);
	
	child[1] = fork();
	//파이프의 복사본을 만든다. child[0] <- pid 
	//1이상이 부모고 0이 자식
	exec_pipe_case_one(child[1], fd, envs, line);
	//1번에도 똑같이 한다.
	
	free(line);
	close(fd[0]);
	close(fd[1]);
	waitpid(child[1], &status[1], 0);
	waitpid(child[0], &status[0], WNOHANG);
}