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

int			parse_pipe(t_cmd *curr)
{
	//할일 : '| ' 만 삭제하는 함수 만들기.
	char *temp;

	if (!(curr->option))
		return (-1);
	temp = curr->option;
	if (ft_strncmp(curr->option, " | ", 3) == 0)
		curr->option = ft_strdup(curr->option + 3);
	else if (ft_strncmp(curr->option, "| ", 2) == 0)
		curr->option = ft_strdup(curr->option + 2);
	else
		return (-1);
	free(temp);
	return (1);
}

int			exec_pipe(t_cmd *curr, t_minishell *minishell)
{
	int		pipe_fd[2];
	//[궁금증] pid는 지역변수이므로, p1과 p2 구분할 필요 없이 돌려쓰기 해도 될 것 같은데 어떻습니까?
	//넵 좋아요! 하나만 쓰죠!
	int		p1, p2;

	//command -> asdfasdfafs
	//option  -> | asdfadfsa | asdfsdafasf

	//[검증 필요] 만약 asadfa | 만 들어왔을 경우 haspipe와 parsepipe는 어떻게 검열합니까?

	if (!(parse_pipe(curr)))
		return (-1);
	//할일 : 파싱 구현 (option의 '| ' 을 없애고 뒷 문자열만 백업하기.)
	//[검증 필요] 이 방식을 채택할 경우 생길 수 있는 문제가 무엇인가요?
	//[가설 1] 이 방식을 채택하면 리다이렉션, 쿼트 실행 함수에서도 각자의 문자를 없애는 기능이 내장되어야 합니다.

	// 2. 파싱한 뒤 pipe(pipe_fd)로 앞서 수행한 명령의 file descriptions을 받는다. 이 배열의 0번은 read, 1번은 write가 된다.
	pipe(pipe_fd);
	// 3. fork 명령어로 새 문자열에다 프로세스를 복사한다.
	p1 = fork();
	//p1이 자식프로세스라면(그러니까 지금 복사한 파이프가 부모라면) -
	if (p1 == 0)
	{
		//p1(pipe1)이 자식이라는 뜻이므로 파이프의 1번구멍을 stdout으로 내뱉는다
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	else
	{
		p2 = fork();
		//그게 아니고, p2가 자식프로세스라면 -
		if (p2 == 0)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO); //파이프의 0번구멍을 stdinn으로 읽어들인다.
			//pipe_fd는 지역변수이고, pipe는 fork로 계속 살아있는 상태이므로 이것이 가능하다.
			close(pipe_fd[0]);
		}
	}
	if (curr->option && curr->option[0] != '\0')
		cmd_executor(minishell, curr->option);//재귀. trim한 line을 상위함수에 넣어서 파이프/리다이렉션/따옴표/달러 그외 순으로 검사한다.
		//현재 재귀가 작동을 안합니다... 해결방법 모색해야함
	return (1);

	//[검증 필요] 이 방식을 채택할 경우 생길 수 있는 문제가 무엇인가요?

	/*
	// 1. 문자열을 받았으면 pipe 이중배열() -> curr->argv에다 파싱해서 입력한다.
	// 4. 만약에 포크로 복사된 프로세스 아이디 p1이 0이다!(자식) 0인 파이프의 경우를 처리하는 함수를 실행시킨다.
	exec_process_zero(p1, pipe_fd, curr, minishell);
	// 5. 여기서 프리를 해주네요???????
	//free();
	// 6. fork 명령어로 두 번째 프로세스복사!
	p2 = fork();
	// 7.포크로 복사된 프로세스 아이디 p2이 1이다! 부모 파이프 경우를 처리하는 함수를 실행시킨다!
	exec_process_one(p2, pipe_fd, curr, minishell);
	// 8. 또 나머지도 프리를 한다!
	//free();
	// 9. 파일 디스크립터 close한다.
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	//10. pid

*/
}

/*
void parse_pipe(t_minishell *minishell, t_cmd *cmd, char *input)
{
	int start = 0;
	int end = 0;

	if (!input)
		return ;
	while (input[end] && end < ft_strlen(input))
	{
		start = end;
		while (input[end] && input[end] != ';')
			end++;
		if (input[end] == ';' || !input[end])
		{
			cmd->next = create_node(minishell, input + start, end - start - 1);
			cmd = cmd->next;
		}
		end++;
	}
}

int			exec_process_zero(pid_t p1, int pipe_fd[2], t_cmd *curr, t_minishell *minishell)
{
	return (1);
}

int			exec_process_one(pid_t p1, int pipe_fd[2], t_cmd *curr, t_minishell *minishell)
{
	return (1);
}

*/