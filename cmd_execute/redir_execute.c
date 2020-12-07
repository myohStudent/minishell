/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:44:47 by myoh              #+#    #+#             */
/*   Updated: 2020/12/07 11:21:39 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		redir2(t_minishell *minishell, t_cmd *scmd, int flag)
{
	int		fd;
	
	if ((fd = open(scmd->next->command, flag, 0644)) < 0)  //str
	{
		ft_printf("에러났음: %s: %s\n", scmd->command, strerror(errno));
		g_command_nb = 1;
		exit(1);
	}
	if (((scmd->type == REDIR) || (scmd->type == FREDIR)) && scmd->fdout)
		close(scmd->fdout);
	if ((scmd->type == DREDIR) && scmd->fdin)
		close(scmd->fdin);
	return (fd);
}

void	redir1(t_minishell *minishell, t_cmd *scmd)
{
	int	i;
	 t_cmd *sscmd;

	 sscmd = scmd;
	i = 0;
	while (sscmd && sscmd->next && i < minishell->cnt)
	{
		ft_printf("dscmd->command : /%s/ \n", sscmd->command);
		if (sscmd->type == REDIR && sscmd->fdout != -1)
			sscmd->fdout = redir2(minishell, scmd, O_TRUNC | O_RDWR | O_CREAT);
		else if (scmd->type == DREDIR && sscmd->fdin != -1)
			sscmd->fdin = redir2(minishell, scmd, O_RDONLY);
		else if (scmd->type == FREDIR && sscmd->fdout != -1)
			sscmd->fdout = redir2(minishell, scmd, O_RDWR | O_CREAT | O_APPEND);
		else
		 	sscmd = sscmd->next;
		i++;
	}
}
/*
int		exec_redir(t_cmd *curr, t_minishell *minishell) 
{
    int     i;
    int     fd;
	t_cmd		*head;
	t_cmd		*redir_cmd;
	
	head = (t_cmd *)malloc(sizeof(t_cmd));
	redir_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	//a glabalized parser needed! >, <, >> 모두 한 번에 파싱? 
	parse_flag(curr, head, minishell, '>');
//	parse_global(curr, head, minishell);
	i = 0;
	redir_cmd = head->next;
	redir_cmd = reverse_node(head);
	while (redir_cmd != NULL)
	{
		ft_printf(" /%s/ ", redir_cmd->command);
		if (redir_cmd->next)
			redir_cmd = redir_cmd->next;
		else
			break ;
	}
	ft_printf("\n");
	free(redir_cmd);
	redir_cmd = head->next;
	redir_cmd = reverse_node(head);
	while (redir_cmd && redir_cmd->next)
    {
        if (!flags[1] && !flags[2] && !flags[3])
			return (-1);
        if (flags[1]) // '>' 수행
        {
			ft_printf("'>' 들어왔다 ");
			flags[1] = 0;

            if ((fd = open(redir_cmd->next->command, O_WRONLY | O_CREAT | O_TRUNC, 0744)) == -1)
                return (-1); //perror 
			ft_printf("file created. \n");
			if (fd < 0)
			{
				ft_printf("No such file or directory");
				return (-1);
			}
			ft_printf("??? ");
        	dup2(fd, 1); //(fd 복사) - 여기서 에러 왜? 
			close(fd);
			ft_printf("*** ");
			exec_else(minishell, redir_cmd); 
			ft_printf("--- ");
		}
		else if (flags[2]) // '<' 수행
		{
			ft_printf("> 들어왔다 ");
			flags[2] = 0;
			


		}
		else if (flags[3]) // '>>' 수행
		{
			ft_printf(">> 들어왔다 ");
			flags[3] = 0;
			if ((fd = open(redir_cmd->next->command, O_RDWR | O_CREAT | O_APPEND, 0744)) == -1)
                return (-1); //perror 
			ft_printf("file created. \n");
			if (fd < 0)
			{
				ft_printf("No such file or directory");
				return (-1);
			}
			ft_printf("??? ");
        	dup2(fd, 1); //(fd 복사) - 여기서 에러 왜? 
			close(fd);
			ft_printf("*** ");
			exec_else(minishell, redir_cmd); 
			ft_printf("--- ");
		}
        redir_cmd->command = NULL;
        redir_cmd->next->command = NULL;
        if (redir_cmd != NULL)
        {
            redir_cmd->next = redir_cmd->next->next;
            redir_cmd = redir_cmd->next;
        }
    	redir_cmd->command = NULL;
    }
    return (1);
}

int		exec_dredir(t_cmd *curr, t_minishell *minishell) 
{
    int     i;
    int     fd;
	t_cmd		*head;
	t_cmd		*redir_cmd;
	
	head = (t_cmd *)malloc(sizeof(t_cmd));
	redir_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	parse_flag(curr, head, minishell, '>');
//	parse_global(curr, head, minishell);
	i = 0;
	redir_cmd = head->next;
	redir_cmd = reverse_node(head);
	while (redir_cmd != NULL)
	{
		ft_printf(" /%s/ ", redir_cmd->command);
		if (redir_cmd->next)
			redir_cmd = redir_cmd->next;
		else
			break ;
	}
	ft_printf("\n");
	free(redir_cmd);
	redir_cmd = head->next;
	redir_cmd = reverse_node(head);
	if (redir_cmd)
    {
        if (!redir_cmd->next)
            return (-1);
        else // 리다이렉션 파일 생성하기 (다음 명령어를 상대로 열기 수행)
        {
            if ((fd = open(redir_cmd->command, O_WRONLY | O_CREAT | O_TRUNC, 0744)) == -1)
                return (-1); //perror 
			ft_printf("file created. \n");
        }
		if (fd < 0)
		{
			ft_printf("No such file or directory");
			return (-1);
		}
		ft_printf("??? ");
        dup2(fd, STDOUT_FILENO); //(fd 복사)
		close(fd);
		exec_else(minishell, redir_cmd); 

        redir_cmd->command = NULL;
        redir_cmd->next->command = NULL;
        if (redir_cmd != NULL)
        {
            redir_cmd->next = redir_cmd->next->next;
            redir_cmd = redir_cmd->next;
        }
    	redir_cmd->command = NULL;
    }
    return (1);
}
*/
//////////////////////////////////////////////////////
/*void	free_redir(t_sym *sym)
{
	ft_strdel(&sym->str);
	free(sym);
}

t_sym		*remove_redir(t_sym *sym, t_sym **start)
{
	t_sym	*sym_temp;
	t_sym	*next;

	sym_temp = *start;
	if (*start == sym)
	{
		next = (*start)->next;
		free_redir(*start);
		*start = next;
		next ? next->prev = NULL : 0;
		return (next);
	}
	while (sym_temp)
	{
		if (sym_temp == sym && sym_temp->prev)
		{
			next = sym_temp->next;
			sym_temp->prev->next = next;
			sym_temp->next ? sym_temp->next->prev = sym_temp->prev : 0;
			free_redir(sym);
			return (next);
		}
		sym_temp = sym_temp->next;
	}
	return (NULL);
}*/