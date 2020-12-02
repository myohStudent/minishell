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


void	pipe_prog2(t_minishell *minishell, t_cmd *curr, pid_t pid, int pipe_fd[2])
{
	int		stat;
	int		pipe_s[2];

	if (pipe(pipe_s) < 0)
		return ;
	if (curr->type == PIPE)
	{
		//process_args(curr->next); //$ ' " " 작업
		redir1(minishell, curr->next);
		while (curr->next && !curr->next->command)
		{
			//process_args(curr->next);
			redir1(minishell, curr->next);
			curr = curr->next;
		}
		if (curr->next) 
			pipe_prog(minishell, curr->next, pipe_fd, pipe_s);
		else
			ft_printf(" 없음 ");
	}
	ft_printf(" pipe_prog2 실행중");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(pipe_s[1]);
	close(pipe_s[0]);
	ft_printf(" 되나? ");
	waitpid(pid, &stat, WUNTRACED);
	while (!WIFEXITED(stat))
		if (!WIFSIGNALED(stat) || curr->type == PIPE)
			break ;
	if (WIFEXITED(stat) && curr->type != PIPE)
		return ;	
}

void	create_fd(t_cmd *curr, int pipe_fd[2], int pipe_s[2])
{
	if (curr->prev && curr->prev->type == PIPE)
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		if (curr->type == PIPE)
		{
			dup2(pipe_s[1], 1);
			close(pipe_s[0]);
		}
	}
	else if (curr->type == PIPE)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
	}
	if (curr->fdout)
	{
		dup2(curr->fdout, STDOUT_FILENO);
		close(curr->fdout);
	}
	if (curr->fdin)
	{
		dup2(curr->fdin, STDIN_FILENO);
		close(curr->fdin);
	}
}

int		exec_ve(t_minishell *minishell, t_cmd *curr)
{
	ft_printf("exec_ve 들어옴 \n");
	if (ft_strncmp(curr->command, "echo\0", 5) == 0)
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
	else if (ft_strncmp(curr->command, "cd\0", 3) == 0)
	{
		if (curr->argc == 1)
		{
			if (chdir(home_dir) < 0)
				return (-1);
		}
		else if (!curr->option)
		{
			if (chdir(home_dir) < 0)
				return (-1);
		}
	}
	else if (ft_strncmp(curr->command, "exit\0", 5) == 0)
		cmd_exit(curr, minishell);
	else if (ft_strncmp(curr->command, "env\0", 4) == 0)
		print_env(minishell->env_list);
	if (ft_strncmp(curr->command, "pwd\0", 4) == 0)
	{
		if (curr->argc == 1 || curr->option == NULL)
			ft_putstr_fd(getcwd(minishell->path, 4096), 1);
		else if (curr->argc > 1 && curr->option)
			ft_putstr_fd("pwd: too many arguments", 1);
		else if (curr->argc > 1)
			ft_putstr_fd(getcwd(minishell->path, 4096), 1);
		ft_putchar('\n');
	}
	else if (ft_strncmp(curr->command, "export\0", 7) == 0)
		cmd_export(curr, minishell);
	else if (ft_strncmp(curr->command, "unset\0", 5) == 0)
		cmd_unset(curr, minishell);
	else if (curr->command && minishell->environ != NULL && curr->pipe_array != NULL)
	{
		execve(curr->pipe_bin, curr->pipe_array, minishell->environ);
		ft_printf("%s: command not found\n", curr->command);
		exit(1);
	}
	return (0);
}

void	pipe_prog(t_minishell *minishell, t_cmd *scmd, int pipe_fd[2], int pipe_s[2])
{
	pid_t	pid;

	minishell->forked = 1;
	scmd->pipe_array = store_commands(scmd, minishell); //execve용 명령어 배열 정리하는 함수
	scmd->pipe_bin = get_bin(minishell, scmd->command); 
	pid = fork();
	if (pid == 0)
	{

		scmd->fdout == -1 || scmd->fdin == -1 ? exit(1) : 0;
		create_fd(scmd, pipe_fd, pipe_s);
	 	exec_ve(minishell, scmd);
	}
	else if (pid < 0)
	 	return ; //error;
	else
	{
		if (scmd->type == PIPE && scmd->prev && scmd->prev->type == PIPE && !close(pipe_fd[1]) && !close(pipe_fd[0]))
	 	{
			 pipe_prog2(minishell, scmd, pid, pipe_s);
		}
	 	else
	 		pipe_prog2(minishell, scmd, pid, pipe_s);
	}
}

/*
void 		exec_child(int *pipe_fd, t_minishell *minishell, t_cmd *curr)
{
	//ft_printf("p2 : ");
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 1); //파이프의 0번구멍을 stdinn으로 읽어들인다.
	exec_else(minishell, curr);
	close(pipe_fd[0]);
	exit(1);	
}

void		exec_parent(int *pipe_fd, t_minishell *minishell, t_cmd *curr)
{
		//ft_printf("p1 : ");
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 0);
		//execve(curr->command, &curr->command, minishell->environ);
		//execve(pipe1, &pipe_cmdlist[1], minishell->environ);
		exec_else(minishell, curr);
		close(pipe_fd[1]);
		exit(1);
}

void		parse_pipe(char **str)
{
	int		i;

	i = 0;
	if (*str)
	{
		while ((*str)[i] == ' ')
			i++;
		(*str) = ft_strdup((*str) + i);
		if ((*str)[i] == '|')
			i++;
		(*str) = ft_strdup((*str) + i);
		while ((*str)[i] == ' ')
			i++;
		(*str) = ft_strdup((*str) + i);
		
	}
}

int			parse_global2(t_cmd *curr, t_cmd *pipe_cmd, t_minishell *minishell)
{ 
	int		i;
	int		j;
	char		*temp;
	char		*temp2;
	char		*temp3;
	t_cmd	*next;
	
	i = 0;
	temp = ft_strjoin(curr->command, " ");
	temp = ft_strjoin(temp, curr->option);
	//ft_printf("%s\n", temp);
	curr = curr->next;
	pipe_cmd->next = NULL;
	if (temp != NULL)
	{
		delete_space_flag(&temp, '|');
		i = 0;
		if (temp != NULL)
		{
			while (temp[i])
			{ 
				while (temp[i] == '|' && temp[i + 1] != '\0')
				{
					temp2 = ft_substr(temp, 0, i);
					//option 넣는 거랑 redir 파싱이 여기 들어가야 함.
					add_node(pipe_cmd, space_trim(temp2));
					free(temp2);
					free(temp);
					temp = ft_substr(temp, i + 1, ft_strlen(temp) - i);
					temp2 = NULL;
					i = -1;
				}
				i++;
			}
			if (temp) // 마지막 cmd
			{
				add_node(pipe_cmd, space_trim(temp));
				temp = NULL;
				free(temp);
			}
			free(temp2);				
		}
	}
	return (1);
}

int			exec_pipe(t_cmd *curr, t_minishell *minishell)
{
	int			i;
	int			pipe_fd[2];
	int			stat;
	pid_t		pid;
	t_cmd		*head;
	t_cmd		*pipe_cmd;
	int			ffd;

	ffd = 0;
	head = (t_cmd *)malloc(sizeof(t_cmd));
	pipe_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	//parse_global2(curr, head, minishell);
	parse_flag(curr, head, minishell, '|');
	i = 0;
	pipe_cmd = head->next;
	pipe_cmd = reverse_node(head);
	while (pipe_cmd != NULL)
	{
		ft_printf(" /%s/ ", pipe_cmd->command);
		if (pipe_cmd->next)
			pipe_cmd = pipe_cmd->next;
		else
			break ;
	}
	ft_printf("\n");
	while (pipe_cmd != NULL)
	{
		if (pipe(pipe_fd) < 0)
			return (-1);	
		//ft_printf("fd0: %d, fd1: %d ", pipe_fd[0], pipe_fd[1]);			
		if ((pid = fork()) == -1) 
		{
			perror("fork");
			exit(1);
		}
		////////////////// pipe 수정할 부분 ////////////////////
		if (pid == 0) 
			exec_parent(pipe_fd, minishell, pipe_cmd);
		else
			wait(NULL);
		if ((pid = fork()) < 0)
			return (-1); 
		if (pid == 0)
			exec_child(pipe_fd, minishell, curr);
		else
			wait(NULL);
		if (pipe_cmd->next)
			pipe_cmd = pipe_cmd->next;
		else
		{
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			return (1);
		}
	}
		if (pid == 0) 
		{
			dup2(ffd, 0);
			if (pipe_cmd->next != NULL) 
			{
				dup2(pipe_fd[1], 1);
			}
			exec_else(minishell, pipe_cmd);
			close(pipe_fd[0]);
			exit(1);
		}
		else 
		{
			wait(NULL); 		
			close(pipe_fd[1]);
			ffd = pipe_fd[0];
		}
		if (pipe_cmd->next)
		{
			ft_printf("else ");
			exec_else(minishell, pipe_cmd);
			pipe_cmd = pipe_cmd->next;
			}
		else
			return (1);
		if (pid == 0) 
			exec_parent(pipe_fd, minishell, pipe_cmd);
		else
			wait(NULL);
		if ((pid = fork()) < 0)
			return (-1); 
		if (pid == 0)
			exec_child(pipe_fd, minishell, curr);
		else
			wait(NULL);
		if (pipe_cmd->next)
			pipe_cmd = pipe_cmd->next;
		else
		{
			//execve(pipe_cmd->command, &pipe_cmd->command, minishell->environ);
			exec_else(minishell, pipe_cmd); 
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			return (1);
		}
	//if (curr->option && curr->option[0] != '\0')
		//cmd_executer(minishell, curr->option);

		//////////////////////////////////////////////
	}
	return (-1);
}*/