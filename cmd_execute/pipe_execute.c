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

//파싱 다시 해 보기
void		parse_pipe3(char **raw_input, char **parsed_input)
{ // 이중 포인터를 써야 값이 입력된다.
	int		i;
	char	*temp1;
	char	*temp2;

	i = 0;
	// 앞뒤 공백 없이 파이프 입력일 때의 예외처리가 되지 않았음.
	while ((*raw_input)[i])
	{
		if ((*raw_input)[i] == '|')
		{
			
			temp1 = ft_substr((*raw_input), 0, i); // | 앞까지 잘라 temp1에 저장한다.
			(*parsed_input) = ft_strtrim(temp1, " "); // 스페이스를 트림하여 저장
			free(temp1);
			temp1 = ft_substr((*raw_input), i + 1, ft_strlen(*raw_input) - i);
			// 그 나머지를 temp1 저장
			temp2 = ft_strtrim(temp1, " "); // 다시 space 트림하여 temp2에 저장
			free(temp1);
			(*raw_input) = temp2; // 그 나머지가 raw_input에 다시 들어온다. 
			free(temp2);
			return ; // 하나씩 처리하고 마지막에 | 없을 때 처리 안 하기
		}
		i++;
	}
}

void		exec_parent(int *pipe_fd, t_minishell *minishell, t_cmd *curr)
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	exec_else(minishell, curr);
	ft_printf("\n");
	ft_printf("p1 수행 ");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(1);
}

void 		exec_child(int *pipe_fd, t_minishell *minishell, t_cmd *curr)
{
	//close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO); //파이프의 0번구멍을 stdinn으로 읽어들인다.
		//pipe_fd는 지역변수이고, pipe는 fork로 계속 살아있는 상태이므로 이것이 가능하다.
	exec_else(minishell, curr);
	ft_printf("p2 수행 \n");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(1);

}

int			parse_pipe2(t_cmd *curr, t_minishell *minishell)
{
	//할일 : '| ' 만 삭제하는 함수 만들기.
	char *temp;

	temp = curr->option;
	ft_printf("curr->option: %s\n", curr->option);

	if ((ft_strncmp(curr->option, " | ", 3) == 0))
		curr->option = ft_strdup(curr->option + 3);
	else if ((ft_strncmp(curr->option, " || ", 4) == 0)) //이거 이런 식으로 예외가 많은 듯....ㅠ
		curr->option = ft_strdup(curr->option + 4);
	else if (ft_strncmp(curr->option, "| ", 2) == 0)
		curr->option = ft_strdup(curr->option + 2);
	else
		return (-1);
	ft_printf("curr->option: %s\n", curr->option);
	//free(temp);
	//ft_printf("curr->option: %s\n", curr->option);
	//parsed_input = parse_pipe2(raw_input); //세미콜론마다 잘라서 문자열에 저장해 준다
	//parse_pipe3(&raw_input, &parsed_input);
	//ft_printf("raw: %s, parsed input : %s\n", raw_input, parsed_input);
	/*if (!(curr->option))
		return (-1);
	temp = curr->option;
	if ((ft_strncmp(curr->option, " | ", 3) == 0))
		curr->option = ft_strdup(curr->option + 3);
	else if ((ft_strncmp(curr->option, " || ", 4) == 0)) //이거 이런 식으로 예외가 많은 듯....ㅠ
		curr->option = ft_strdup(curr->option + 4);
	else if (ft_strncmp(curr->option, "| ", 2) == 0)
		curr->option = ft_strdup(curr->option + 2);
	else
		return (-1);*/
	
	//free(temp);
	//ft_printf("curr->option: %s\n", curr->option);
	return (1);
}

void			exec_pipe(t_cmd *curr, t_minishell *minishell)
{
	int		pipe_fd[2];
	//[궁금증] pid는 지역변수이므로, p1과 p2 구분할 필요 없이 돌려쓰기 해도 될 것 같은데 어떻습니까?
	//넵 좋아요! 하나만 쓰죠!
	pid_t	p1, p2;
	int		cond1 = 0;
	int		cond2 = 0;
	//parse_pipe3(&raw_input, &parsed_input);
	//ft_printf("piped_input: %s \n", parsed_input);

	//command -> asdfasdfafs
	//option  -> | asdfadfsa | asdfsdafasf
		// 잘 안 돼서 input을 전역변수로 가져와서 파이프 전용으로 파싱 처리를 다시 했습니다!   
	//[검증 필요] 만약 asadfa | 만 들어왔을 경우 haspipe와 parsepipe는 어떻게 검열합니까?
	//뒷문자열 생략시키기
	parse_pipe2(curr, minishell);
	//할일 : 파싱 구현 (option의 '| ' 을 없애고 뒷 문자열만 백업하기.)
	//[검증 필요] 이 방식을 채택할 경우 생길 수 있는 문제가 무엇인가요?
	//[가설 1] 이 방식을 채택하면 리다이렉션, 쿼트 실행 함수에서도 각자의 문자를 없애는 기능이 내장되어야 합니다.

	// 2. 파싱한 뒤 pipe(pipe_fd)로 앞서 수행한 명령의 file descriptions을 받는다. 이 배열의 0번은 read, 1번은 write가 된다.
	if (pipe(pipe_fd) < 0)
		return ;
	// 3. fork 명령어로 새 문자열에다 프로세스를 복사한다.
	if ((p1 = fork()) < 0)
		return ;
	wait(&cond1);
	//p1이 자식프로세스라면(그러니까 지금 복사한 파이프가 부모라면) -
	//p1(pipe1)이 자식이라는 뜻이므로 파이프의 1번구멍을 stdout으로 내뱉는다
	if (p1 == 0) //0보다 크면 자식 프로세스를 기다림.
		exec_parent(pipe_fd, minishell, curr);
	ft_printf("p1: %d ", p1);
	//waitpid(pipe_fd[0], &cond2, WNOHANG);
	if ((p2 = fork()) < 0)
		return ; 
	//그게 아니고, p2가 자식프로세스라면 -
	ft_printf("p2: %d ", p2);
	if (p2 == 0)
		exec_child(pipe_fd, minishell, curr);
	//if (curr->option && curr->option[0] != '\0')
		//cmd_executer(minishell, curr->option);//재귀. trim한 line을 상위함수에 넣어서 파이프/리다이렉션/따옴표/달러 그외 순으로 검사한다.
		//현재 재귀가 작동을 안합니다... 해결방법 모색해야함 
		//안 되네요 파싱 따로 해도 안 되네요...

	//waitpid(pipe_fd[1], &cond1, WNOHANG); //무조건 리턴됨. 중단되었다가 재개된 자식프로세스의 상태를 받음.
	//[검증 필요] 이 방식을 채택할 경우 생길 수 있는 문제가 무엇인가요?
	wait(&cond2);
	free(parsed_input);
	return ;
}