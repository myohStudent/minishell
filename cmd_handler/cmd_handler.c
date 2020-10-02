/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 02:54:57 by seohchoi          #+#    #+#             */
/*   Updated: 2020/10/02 17:53:32 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int cmd_handler(t_minishell *minishell)
{
	char buf[2];
	char *input;
	t_cmd *curr;

	//init
	minishell->cmd_num = 0;
	//

	buf[0] = ' ';
	buf[1] = '\0';
	input = ft_strdup("");
	while (buf[0] != '\n')
	{
		read(STDIN_FILENO, buf, 1);
		if (buf[0] != '\n')
			input = ft_strjoin(input, buf);
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

	//[해결] 할일 : 이하 내용을 parse 함수에 담기
	//[해결] 할일 : parse_input에서 ; 별로 명령어 나누는 처리 해줘야함(linked list 사용해야할듯)
	//[해결] 할일 : 라인 끝자락에 공백이 들어갔을 경우 argc 추가하지않기.

	minishell->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	parse_cmd(minishell->cmd, input);
	curr = minishell->cmd->next; // 헤드 노드

	//할일 : 이하 내용을 담을 함수 만들기 (명령어 처리기)

	int i = 0;
	while (curr != NULL && *input != 0)               // 포인터가 NULL이 아닐 때 계속 반복
    {
        //ft_printf("%d", i);    // 현재 노드의 데이터 출력
	   	i++;
		//ft_printf(" : %s|", curr->command);
		//할일 : 명령어별로 함수 분할하기. 함수마다 노드가 비어있는 경우 return -1 처리하기.
		if (curr->command)
		{
			if (ft_strncmp(curr->command, "pwd\0", 4) == 0)
			{
				if (curr->argc == 1)
					ft_putstr_fd(getcwd(minishell->path, 4096), 1);
				else
					ft_putstr_fd("pwd: too many arguments", 1);
				ft_putchar('\n');
			}
			else if (ft_strncmp(curr->command, "cd\0", 3) == 0)
			{
				if (curr->argc == 1)
				{
					int i = 0;
					while (minishell->env_temp[i])
					{
						if (ft_strncmp(minishell->env_temp[i], "HOME\0", 5) == 0)
							chdir(minishell->env_temp[i + 1]);
						i++;
					}
					return (-1);
				}
				else if (curr->argc == 2)
				{
					if (chdir(curr->option) < 0) //경로가 실제 존재하는지 체크합니다.
						ft_putstr_fd("cd: no such file or directory\n", 1);
				}
				else if (curr->argc > 2)
					ft_putstr_fd("cd: too many arguments\n", 1);
			}
			else if (ft_strncmp(curr->command, "echo\0", 5) == 0)
			{
				if (curr->option && ft_strncmp(curr->option, "-n", 2) == 0)
					ft_putstr_fd(curr->option + 3, 1);
				else
				{
					if (curr->option)
						ft_putstr_fd(curr->option, 1);
					ft_putchar('\n');
				}
			}
			else if (ft_strncmp(curr->command, "exit\0", 5) == 0)
			{
				ft_putstr_fd("\n[Process Completed]", 1);
				exit(1);
			}
			else if (ft_strncmp(curr->command, "env\0", 4) == 0)
				cmd_env(minishell);
			else if (ft_strncmp(curr->command, "export\0", 7) == 0)
				cmd_export(curr, minishell);
			else
				ft_printf("command not found: %s\n", curr->command);	
		}
		t_cmd *next;
		next = curr->next;
		free(curr);
		curr = next;
    }
	free(input);
	free (minishell->cmd);
	return (1);
}