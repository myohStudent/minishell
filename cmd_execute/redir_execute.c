/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:44:47 by myoh              #+#    #+#             */
/*   Updated: 2020/11/28 17:49:10 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//
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
/*	redir_cmd = head->next;
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
	free(redir_cmd);*/
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
/* 깃헙에 있는 거 가져옴!
int redirect(char * input, char * output, char * error){
	int fd;
	
	//Redirección de entrada.
	if(input != NULL){
		fd = open(input,O_RDONLY);
		if(fd == -1){
			printf("%s, Error: fallo en apertura de fichero.\n",input);
			exit(1);
		}else{
			dup2(fd,0);
			close(fd);
		}
	}
	//Redireccion de salida
	if(output != NULL){
		fd = creat(output,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if(fd == -1){
			printf("%s, Error: fallo en apertura o creacion de fichero.\n",output);
			exit(1);
		}else{
			dup2(fd,1);
			close(fd);
		}
	}
	//Redireccion de error
	if(error != NULL){
		fd = creat(error,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if(fd == -1){
			printf("%s, Error: fallo en apertura o creacion de fichero.\n",error);
			exit(1);
		}else{
			dup2(fd,2);
			close(fd);
		}
	}
	return EXIT_SUCCESS;
}
*/