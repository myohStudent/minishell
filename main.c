/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 02:55:05 by seohchoi          #+#    #+#             */
/*   Updated: 2021/01/08 02:57:50 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void			display_prompt(void)
{
	ft_putstr_fd("\033[0;31mm", 1);
	ft_putstr_fd("\033[1;32mi", 1);
	ft_putstr_fd("\033[1;36mn", 1);
	ft_putstr_fd("\033[0;35mi", 1);
	ft_putstr_fd("\033[0;33ms", 1);
	ft_putstr_fd("\033[1;31mh", 1);
	ft_putstr_fd("\033[0;36me", 1);
	ft_putstr_fd("\033[0;35ml", 1);
	ft_putstr_fd("\033[1;33ml", 1);
	ft_putstr_fd("\033[1;35m > ", 1);
	ft_putstr_fd("\033[0m", 1);
}

int				main(int ac, char **av, char **env)
{
	t_minishell	minishell;

	welcome_shell();
	minishell.env_list = (t_env *)malloc(sizeof(t_env));
	init_env(env, &minishell, minishell.env_list);
	get_envp(env, minishell.env_currnb);
	minishell.path = getcwd(NULL, 0);
	while (1)
	{
		display_prompt();
		signal(SIGINT, parent_signal_handler);
		signal(SIGQUIT, parent_signal_handler);
		if (g_sigexit != 1 && g_sigexit != 2)
			cmd_handler(&minishell);
	}
	free(minishell.env_list);
	return (0);
}
