/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:30:15 by myoh              #+#    #+#             */
/*   Updated: 2020/10/25 15:49:255 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		exec_parent(int *pipe_fd, t_minishell *minishell, t_cmd *curr, int i)
{
	//close(pipe_fd[i]);
	dup2(pipe_fd[(i * 2) + 1], STDOUT_FILENO);
	ft_printf("p1 : ");
	execve(curr->command, &curr->command, minishell->environ);
	//execve(pipe1, &pipe_cmdlist[1], minishell->environ);
	//exec_else(minishell, curr); // pipe용 exec_else를 다시 만들어야 함.. ㅠㅠ
	//close(pipe_fd[i + 1]);
	exit(1);
}

void 		exec_child(int *pipe_fd, t_minishell *minishell, t_cmd *curr, int i)
{
	//close(pipe_fd[i + 1]);
	dup2(pipe_fd[(i - 1) * 2], STDIN_FILENO); //파이프의 0번구멍을 stdinn으로 읽어들인다.
	//pipe_fd는 지역변수이고, pipe는 fork로 계속 살아있는 상태이므로 이것이 가능하다.
	ft_printf("p2 : ");
	if (curr->next->command)
		execve(curr->command, &curr->next->command, minishell->environ);
	// execve(pipe1, &pipe_cmdlist[0], minishell->environ);
	exec_else(minishell, curr);
	//close(pipe_fd[i]);
	exit(1);
	
}

void		parse_pipe(char **temp)
{
	int		i;

	i = 0;
	if (*temp)
	{
		while ((*temp)[i] == ' ')
			i++;
		(*temp) = ft_strdup((*temp) + i);
		i = 0;
		if ((*temp)[i] == '|')
			i++;
		(*temp) = ft_strdup((*temp) + i);
		while ((*temp)[i] == ' ')
			i++;
		(*temp) = ft_strdup((*temp) + i);
		/*
		if ((ft_strncmp(s, " | ", 3) == 0))
		s = ft_strdup(s + 3);
	else if ((ft_strncmp(s, " | ", 3) == 0)) 
		s = ft_strdup(s + 4);
	else if (ft_strncmp(s, "| ", 2) == 0)
		s = ft_strdup(s + 2);
	else if ((ft_strncmp(s, "|", 1) == 0))
		s = ft_strdup(s + 1);
	*/
	}
}

int			parse_global2(t_cmd *curr, t_minishell *minishell)
{ //curr->option을 모두 연결리스트화하기
	int		i;
	char	*temp;
	char	*temp2;
	t_cmd	*next = malloc(sizeof(t_cmd));
	int		j;

	j = 0;
	i = 0;
	temp = ft_strdup(curr->option);
	curr->option = NULL;
	while (temp && temp != NULL)
	{
		parse_pipe(&temp);
		
		j = is_char('|', temp);
		minishell->pipe_num = j + 1;
		ft_printf("temp: /%s/ j: %d\n", temp, j);
		curr->next = next;
		next->command = ft_substr(temp, 0, j);
		if (j > 0)	
		{
			temp2 = ft_substr(temp, j, ft_strlen(temp));
			temp = ft_strdup(temp2);
			free(temp2);
		}
		else if (j == -1)
			temp = NULL;
		ft_printf("temp나머지: %s ", temp);
	}
	free(temp);
	return (1);
}

int			parse_global(t_cmd *curr, t_minishell *minishell)
{
	int		i;
	char	*temp;
	t_cmd	*next = malloc(sizeof(t_cmd));
	
	i = 0;
	temp = curr->option;
	
	parse_pipe(&temp);
	curr->next = next;
	next->command = curr->option;
	curr->option = NULL;
	free(temp);
	return (1);
}

void			exec_pipe(t_cmd *curr, t_minishell *minishell)
{
	int i;
	int j;
	i = 0;
	j = 0;
	int		pipe_fd[pipe_num * 2];
	pid_t	pid;
	ft_printf("pipe_num: %d ", pipe_num);

	// parse_pipe3(&raw_input, &parsed_input);
	//command -> asdfasdfafs
	//option  -> | asdfadfsa | asdfsdafasf
	//[검증 필요] 만약 asadfa | 만 들어왔을 경우 haspipe와 parsepipe는 어떻게 검열합니까?
	//뒷문자열 생략시키기
	//parse_global(curr, minishell);
	//할일 : 파싱 구현 (option의 '| ' 을 없애고 뒷 문자열만 백업하기.)
	//[검증 필요] 이 방식을 채택할 경우 생길 수 있는 문제가 무엇인가요?
	//[가설 1] 이 방식을 채택하면 리다이렉션, 쿼트 실행 함수에서도 각자의 문자를 없애는 기능이 내장되어야 합니다.
	// 2. 파싱한 뒤 pipe(pipe_fd)로 앞서 수행한 명령의 file descriptions을 받는다. 이 배열의 0번은 read, 1번은 write가 된다.
	parse_global2(curr, minishell);
	ft_printf("pipe_num: %d ", pipe_num);
	while (i < pipe_num)
	{
		if (pipe(pipe_fd + i * 2) < 0)
			return ;
		ft_printf("pipe_fd[%d]: %d \n", i, pipe_fd[i]);
		i++;
	}
	i = 0;
	while (curr->command != NULL && i < pipe_num)
	{
		if ((pid = fork()) < 0)
			return ;
		if (pid == 0)
		{
			exec_parent(pipe_fd, minishell, curr, i);
			/*if (j != 0)
				dup2(pipe_fd[j - 2], 0);
			if ((curr->next)->command != NULL)
				dup2(pipe_fd[j + 1], 1);
			while (i < minishell->pipe_num)
				close(pipe_fd[i++]);
			if (execve(curr->command, &curr->command, minishell->environ))
				exit(1);*/
		}
		else
			wait(NULL);
		if ((pid = fork()) < 0)
			return ; 
		if (pid == 0)
			exec_child(pipe_fd, minishell, curr, i);
		else
			wait(NULL);
		if ((curr->next)->command != NULL)
		{
			curr->command = (curr->next)->command;
		}
		while (i < minishell->pipe_num)
				close(pipe_fd[i++]);
		i++;
	}
		/*else
		{
			if (curr->command != NULL)
				curr->command = (curr->next)->command;
			j += 2;
			i = 0;
			while (i < minishell->pipe_num)
				close(pipe_fd[i++]);
		}
		while (waitpid(0, 0, 0) < 0);*/
/*	
	// 3. fork 명령어로 새 문자열에다 프로세스를 복사한다.
	if ((pid = fork()) < 0)
		return ;
	//p1이 자식프로세스라면(그러니까 지금 복사한 파이프가 부모라면) -
	//p1(pipe1)이 자식이라는 뜻이므로 파이프의 1번구멍을 stdout으로 내뱉는다
	if (pid == 0) //0보다 크면 자식 프로세스를 기다림.
		exec_parent(pipe_fd, minishell, curr);
	else
		wait(NULL);
	if ((pid = fork()) < 0)
		return ; 
	if (pid == 0)
		exec_child(pipe_fd, minishell, curr);
	else
		wait(NULL);
	//if (curr->option && curr->option[0] != '\0')
		//cmd_executer(minishell, curr->option);//재귀. trim한 line을 상위함수에 넣어서 파이프/리다이렉션/따옴표/달러 그외 순으로 검사한다.
		//현재 재귀가 작동을 안합니다... 해결방법 모색해야함 
		//안 되네요 파싱 따로 해도 안 되네요...

	//waitpid(pipe_fd[1], &cond1, WNOHANG); //무조건 리턴됨. 중단되었다가 재개된 자식프로세스의 상태를 받음.
	//[검증 필요] 이 방 채택할 경우 생길 수 있는 문제가 무엇인가요?
	minishell->pipe_num--;
	return ;
	*/
}


//파싱 redirection용이랑 통합해서 하기
/*void		parse_pipe3(char **raw_input, char **parsed_input)
{ // 이중 포인터를 써야 값이 입력된다.
	int		i;
	char	*temp1;
	char	*temp2;
	int		j;
	int		type;
	// t_cmd *연결리스트로 만들기 *prev, *next
	i = 0;
	j = 0;
	// is_space i++
	pipe_cmdlist = (char **)malloc(sizeof(char *) * (has_pipes((*raw_input) + 1)));
	// 앞뒤 공백 없이 파이프 입력일 때의 예외처리가 되지 않았음.
	while ((*raw_input)[i])
	{
		if ((*raw_input)[i] == '|')
		{
			// <, |, >>, >, ; 이면 type에 표기.
			// next = 다음 연결리스트로 만들 구조체 만들기.
			// 별도의 함수로 만들기 -> 말록, 스페이스, \', \", 일 때 다음 칸.
			// 다음리스트->이전 리스트= 다음 리스트
			//이전 리스트가 있다 -> 이전리스트의->다음 리스트 = 다음 리스트.
			//type 인자 체크하기
			// 인자 체크 + 스페이스 넘기기.
			//다음 리스트가 있다 = 다음의 다음 = NULL
			//다음 리스트를 반환 
			temp1 = ft_substr((*raw_input), 0, i); // | 앞까지 잘라 temp1에 저장한다.
			(*parsed_input) = ft_strtrim(temp1, " "); // 스페이스를 트림하여 저장
			pipe1 = ft_strdup(*parsed_input);
			pipe_cmdlist[j] = ft_strdup(pipe1);
			j++;
			free(temp1);
			temp1 = ft_substr((*raw_input), i + 1, ft_strlen(*raw_input) - i);
			// 그 나머지를 temp1 저장
			temp2 = ft_strtrim(temp1, " "); // 다시 space 트림하여 temp2에 저장
			free(temp1);
			(*raw_input) = temp2; // 그 나머지가 raw_input에 다시 들어온다. 
			pipe_cmdlist[j] = ft_strdup((*raw_input));
			j++;
			free(temp2);
			ft_printf("pipe1: %s pipelist: %s \n", pipe1, pipe_cmdlist[1]);
			pipe_cmdlist[j] = NULL;
			return ;// 하나씩 처리하고 마지막에 | 없을 때 처리 안 하기
		}
		i++;
	}
}*/