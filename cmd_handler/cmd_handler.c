/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 02:54:57 by seohchoi          #+#    #+#             */
/*   Updated: 2020/12/11 18:00:47 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exec_else(t_minishell *minishell, t_cmd *curr)
{
	// 할일 : 명령어별로 함수 분할하기. 함수마다 노드가 비어있는 경우 return -1 처리하기.
	if (ft_strncmp(curr->command, "pwd\0", 4) == 0)
		cmd_pwd(curr, minishell);
	else if (ft_strncmp(curr->command, "cd\0", 3) == 0)
	{
		if (cmd_cd(curr, minishell) < 0)
			return (-1);
	}
	else if (ft_strncmp(curr->command, "echo\0", 5) == 0)
		cmd_echo(curr, minishell);
	else if (ft_strncmp(curr->command, "exit\0", 5) == 0)
		cmd_exit(curr, minishell);
	else if (ft_strncmp(curr->command, "env\0", 4) == 0)
		print_env(minishell->env_list);
	else if (ft_strncmp(curr->command, "export\0", 7) == 0)
		cmd_export(curr, minishell);
	else if (ft_strncmp(curr->command, "unset\0", 5) == 0)
		cmd_unset(curr, minishell);
	else
	{
		ft_printf("%s: command not found\n", curr->command);
		g_command_nb = 127;
	}
	return (1);
}

void	clear_scmd(t_cmd *cmd, t_minishell *minishell)
{
	while (cmd)
	{
		if (cmd->command)
			ft_strdel(&cmd->command);
		if (cmd->pipe_bin)
			ft_strdel(&cmd->pipe_bin);
		if (cmd->pipe_array)
			free_arr(cmd->pipe_array);
		if (cmd->option)
			ft_strdel(&cmd->option);
		if (cmd->type)
			cmd->type = 0;
		cmd = cmd->next;
	}
	free(cmd);
}

int cmd_executer(t_minishell *minishell, t_cmd *curr)
{
	if (check_separator(minishell, curr) < 0 ) // quote일 때, 무시한다는 플래그 넣어야 함!
		return (-1);
	// symbol이 있다면 다른 루트로 파싱한다
	if (minishell->pipe_num > 0 || minishell->redir_num > 0)
	{
		parse3(minishell, curr);
		if (minishell->scmd && minishell->pipe_num > 0)
		{
			exec_scmd(minishell);
		 	clear_scmd(minishell->scmd, minishell);
		}
		else 
		{ 
			ft_printf("redir은 파이프부터 고치고\n");
		}
	}
	else if (pipe_num == 0 && dollar_exec(curr, minishell) == 0)
	{
		if (!(exec_else(minishell, curr)))
			return (-1);
	}
	return (1);
}

int cmd_handler(t_minishell *minishell)
{
	char buf[2];
	char *input;
	t_cmd *curr;
	t_cmd *next;
	int b;
	struct stat *buf_stat;
	char temp[15];

	//init
	minishell->cmd_num = 0;
	minishell->forked = 0;
	//

	buf[0] = ' ';
	buf[1] = '\0';
	input = ft_strdup("");
	while (buf[0] != '\n')
	{
		b = read(STDIN_FILENO, buf, 1);
		if (buf[0] != '\n')
			input = ft_strjoin(input, buf);
		if (fstat(b, buf_stat) < 0 && b == 0)
		{
			ft_printf(" exit \n");
		 	exit(1);
		}
		
	}
	/*char *temp;
	if ((temp = search(input, '\\')))
	{
		if (temp[1] == 'n')
		{
			*temp = '\n';
			while(temp[1])
			{
				temp++;
				*temp = temp[1];
			}
		}
	}*/
	//1. 한줄로 받아서 파싱을 하면 파싱을 하면서 연결리스트를 바로바로 만들수있다
	//2. 하나하나씩 하면(isspace가 나왔을 경우 바로 옵션으로 넘어가게 하면) 따로 연결리스트를 만들 필요가 없다

	//할일 : quote, double quote, redirection, pipe 구현
	//할일 : $환경변수 실행, $?실행

	//[해결] 할일 : 이하 내용을 parse 함수에 담기
	//[해결] 할일 : parse_input에서 ; 별로 명령어 나누는 처리 해줘야함(linked list 사용해야할듯)
	//[해결] 할일 : 라인 끝자락에 공백이 들어갔을 경우 argc 추가하지않기.

	minishell->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	//// ", '를 여기에서 먼저 실행한다.
	//while (which_quote(input, minishell))
	// 	prompt_quote(minishell);
	// 파싱
	parse_cmd(minishell, minishell->cmd, input);
	curr = minishell->cmd->next; // 헤드 노드
	//init_curr(curr);
	//[해결]할일 : 이하 내용을 담을 함수 만들기 (명령어 처리기)
	int i = 0;
	while (curr != NULL && *input != 0)               // 포인터가 NULL이 아닐 때 계속 반복
    {
	   	i++;
		if (curr->command)
		{
			if (!(cmd_executer(minishell, curr)))
				return (-1);
			t_cmd *next;
			next = curr->next;
			if (curr->next)
				free(curr);
			curr = next;
		}
    }
	free(input);
	free (minishell->cmd);
	minishell->cmd = 0;
	minishell->pipe_bin = NULL;
	minishell->environ = NULL;
	return (1);
}