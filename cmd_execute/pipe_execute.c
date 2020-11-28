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

void		parse_pipe(char **temp)
{
	int		i;

	i = 0;
	if (*temp)
	{
		while ((*temp)[i] == ' ')
			i++;
		(*temp) = ft_strdup((*temp) + i);
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
	/*while (pipe_cmd != NULL)
	{
		ft_printf(" /%s/ ", pipe_cmd->command);
		if (pipe_cmd->next)
			pipe_cmd = pipe_cmd->next;
		else
			break ;
	}
	ft_printf("\n");*/
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
		/*if (pid == 0) 
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
	}*/
	return (-1);
}


int		parse_sym2(t_sym **temp, t_cmd *curr)
{
	if ((*temp)->type == CHARACTERS && (curr->command || ((*temp)->prev
		&& (*temp)->prev->type == REDIR)))
		add_next_sym(&curr->sym_cmd, create_arg_sym((*temp)->str, (*temp)->type));
	if ((*temp)->type == CHARACTERS && !curr->command && (((*temp)->prev
		&& (*temp)->prev->type != REDIR) || !(*temp)->prev))
		curr->command = ft_strdup((*temp)->str);
	if ((*temp)->type == REDIR)
		add_next_sym(&curr->sym_cmd, create_arg_sym((*temp)->str, (*temp)->type));
	if ((*temp)->type == ENVIRON && !curr->command)
		ft_lstadd_back(&curr->env_list, ft_lstnew(ft_strdup((*temp)->str)));
	if ((*temp)->type == PIPE)
	{
		curr->type = PIPE;
		*temp = (*temp)->next;
		return (0);
	}
	if ((*temp)->type == SEMICOLON)
	{
		curr->type = SEMICOLON;
		*temp = (*temp)->next;
		return (0);
	}
	return (1);
}

void	parse2_symbols(t_minishell *minishell, t_sym **temp)
{
	t_cmd	*curr;

	if ((*temp)->type == NEW_LINE)
	{
		*temp = (*temp)->next;
		return ;
	}
	if (!(curr = ft_calloc(1, sizeof(t_cmd))))
		return ;
	while (*temp)
	{
		if (!parse_sym2(temp, curr))
			break ;
		ft_printf("curr %s\n", curr->command);
		if ((*temp)->type == ENVIRON && curr->command)
			add_next_sym(&curr->sym_cmd, create_arg_sym((*temp)->str, (*temp)->type));
		*temp = (*temp)->next;
	}
	add_next_cmd(&minishell->scmd, curr);
}