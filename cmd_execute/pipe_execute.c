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

void		exec_parent(int *pipe_fd, t_minishell *minishell, t_cmd *curr)
{
	close(pipe_fd[0]);
	//dup2(pipe_fd[1], STDOUT_FILENO);
	execve(curr->command, &curr->command, minishell->environ);
	//execve(pipe1, &pipe_cmdlist[1], minishell->environ);
	exec_else(minishell, curr); // pipe용 exec_else를 다시 만들어야 함.. ㅠㅠ
	ft_printf("p1 : ");
	close(pipe_fd[1]);
	exit(1);
}

void 		exec_child(int *pipe_fd, t_minishell *minishell, t_cmd *curr)
{
	close(pipe_fd[1]);
	//dup2(pipe_fd[0], STDIN_FILENO); //파이프의 0번구멍을 stdinn으로 읽어들인다.
	//pipe_fd는 지역변수이고, pipe는 fork로 계속 살아있는 상태이므로 이것이 가능하다.
	execve(curr->command, &curr->next->command, minishell->environ);
	// execve(pipe1, &pipe_cmdlist[0], minishell->environ);
	exec_else(minishell, curr);
	ft_printf("p2 : ");
	close(pipe_fd[0]);
	exit(1);
	
}

int			parse_pipe(t_cmd *curr, t_minishell *minishell)
{
	int		i;
	char	*temp;
	t_cmd	*next = malloc(sizeof(t_cmd));
	i = 0;
	temp = curr->option;
	if ((ft_strncmp(curr->option, " | ", 3) == 0))
		curr->option = ft_strdup(curr->option + 3);
	else if ((ft_strncmp(curr->option, " || ", 4) == 0)) 
		curr->option = ft_strdup(curr->option + 4);
	else if (ft_strncmp(curr->option, "| ", 2) == 0)
		curr->option = ft_strdup(curr->option + 2);
	else
		return (-1);
	curr->next = next;
	next->command = curr->option;
	curr->option = NULL;
	free(temp);
	return (1);
}

void			exec_pipe(t_cmd *curr, t_minishell *minishell)
{
	int		pipe_fd[2];
	//[궁금증] pid는 지역변수이므로, p1과 p2 구분할 필요 없이 돌려쓰기 해도 될 것 같은데 어떻습니까?
	//넵 좋아요! 하나만 쓰죠!
	pid_t	pid;
	//ft_printf("piped_input: %s \n", parsed_input);
	// parse_pipe3(&raw_input, &parsed_input);
	//command -> asdfasdfafs
	//option  -> | asdfadfsa | asdfsdafasf
	//[검증 필요] 만약 asadfa | 만 들어왔을 경우 haspipe와 parsepipe는 어떻게 검열합니까?
	//뒷문자열 생략시키기
	parse_pipe(curr, minishell);
	//parse_pipe3(&raw_input, &parsed_input);
	//할일 : 파싱 구현 (option의 '| ' 을 없애고 뒷 문자열만 백업하기.)
	//[검증 필요] 이 방식을 채택할 경우 생길 수 있는 문제가 무엇인가요?
	//[가설 1] 이 방식을 채택하면 리다이렉션, 쿼트 실행 함수에서도 각자의 문자를 없애는 기능이 내장되어야 합니다.
	// 2. 파싱한 뒤 pipe(pipe_fd)로 앞서 수행한 명령의 file descriptions을 받는다. 이 배열의 0번은 read, 1번은 write가 된다.
	if (pipe(pipe_fd) < 0)
		return ;
	
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
	//[검증 필요] 이 방식을 채택할 경우 생길 수 있는 문제가 무엇인가요?
	return ;
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