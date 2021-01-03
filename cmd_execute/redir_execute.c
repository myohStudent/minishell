/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:44:47 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 09:52:15 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			do_redir(t_minishell *minishell, t_cmd *scmd)
{
	int		fd;

	if ((fd = open(scmd->next->command, O_RDWR | O_CREAT | O_TRUNC, 0744)) < 0)
	{
		g_sigexit = 1;
		ft_printf("%s: No such file or directory...\n", scmd->command);
		g_command_nb = 127;
		close(fd);
		exit(0);
	}
	if (!(ft_compare(scmd->command, "pwd")) && !(ft_compare(scmd->command, "echo"))
	 	&& !(ft_compare(scmd->command, "env")) && !(ft_compare(scmd->command, "cd"))
	 	&& !(ft_compare(scmd->command, "export")) && !(ft_compare(scmd->command, "unset"))
		&& !(ft_compare(scmd->command, "exit")))
	{	
		 ft_printf("%s: command not found\n", scmd->command);
		 g_sigexit = 1;
		 exit(127);
	}
	dup2(fd, 1);
	close(fd);
	exec_else2(minishell, scmd);
	return (1);
}

int			do_dredir(t_minishell *minishell, t_cmd *scmd)
{
	int		fd;

	if ((fd = open(scmd->next->command, O_RDWR | O_CREAT | O_APPEND, 0644)) < 0)
	{
		ft_printf("%s: %s\n", scmd->command, strerror(errno)); 
		g_command_nb = 1;
		close(fd);
		g_sigexit = 1;
		exit(0);
	}
	if (!(ft_compare(scmd->command, "pwd")) && !(ft_compare(scmd->command, "echo"))
		&& !(ft_compare(scmd->command, "env")) && !(ft_compare(scmd->command, "cd"))
	 	&& !(ft_compare(scmd->command, "export")) && !(ft_compare(scmd->command, "unset"))
		&& !(ft_compare(scmd->command, "exit")))
	{
		 ft_printf("%s: command not found\n", scmd->command);
		 g_sigexit = 1;
		 exit(127);
	}
	dup2(fd, 1);
	close(fd);
	exec_else2(minishell, scmd);
	return (1);
}

int			do_bredir(t_minishell *minishell, t_cmd *scmd)
{
	int		fd;

	if ((fd = open(scmd->next->command, O_RDONLY, 0644)) < 0)
	{
		g_sigexit = 1;
		ft_printf("%s: %s\n", scmd->next->command, strerror(errno)); 
		close(fd);
		g_command_nb = 1;
		exit(0);
	}
	if (!(ft_compare(scmd->command, "pwd")) && !(ft_compare(scmd->command, "echo"))
	 	&& !(ft_compare(scmd->command, "env")) && !(ft_compare(scmd->command, "cd"))
	 	&& !(ft_compare(scmd->command, "export")) && !(ft_compare(scmd->command, "unset"))
		&& !(ft_compare(scmd->command, "exit")))
	{
		g_sigexit = 1;
		ft_printf("%s: command not found\n", scmd->command);
		exit(127);
	}
	exec_else2(minishell, scmd);
	dup2(fd, 1);
	close(fd);
	return (1);
}