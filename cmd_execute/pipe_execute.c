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

int			parse_pipe(t_cmd *curr, t_minishell *minishell)
{
	//while (curr->)
	return (1);
}

int			exec_process_zero(pid_t p1, int pipe_fd[2], t_cmd *curr, t_minishell *minishell)
{
	return (1);
}

int			exec_process_one(pid_t p1, int pipe_fd[2], t_cmd *curr, t_minishell *minishell)
{
	return (1);
}

int			exec_pipe(t_cmd *curr, t_minishell *minishell)
{
	int		pipe_fd[2];
	pid_t	p1, p2;

	// 1. 문자열을 받았으면 pipe 이중배열() -> curr->argv에다 파싱해서 입력한다.
	parse_pipe(curr, minishell);
	// 2. 파싱한 뒤 pipe(pipe_fd)로 앞서 수행한 명령의 file descriptions을 받는다. 이 배열의 0번은 read, 1번은 write가 된다.
	pipe(pipe_fd);
	// 3. fork 명령어로 새 문자열에다 프로세스를 복사한다.
	p1 = fork();
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

	return (1);
}

/*void parse_cmd(t_minishell *minishell, t_cmd *cmd, char *input)
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
*/