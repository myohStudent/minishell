/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 02:55:05 by seohchoi          #+#    #+#             */
/*   Updated: 2020/11/15 15:34:58 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./minishell.h"

void		init_env(char **env, t_minishell *minishell, t_env *env_list)
{
	int		i;
	char	**str;

	i = 0;
	minishell->env_initnb = 0;
	while (env[i])
	{
		env_list->next = (t_env *)malloc(sizeof(t_env));
		str = ft_split(env[i], '='); // split해서 나눠 놓기
		if (ft_strncmp(str[0], "HOME\0", 5) == 0)
			home_dir = ft_strdup(str[1]);
		env_list->variable = ft_strdup(str[0]);
		env_list->value = ft_strdup(str[1]);
		env_list = env_list->next;
		free_arr(str);
		minishell->env_initnb++;
		i++;
	}
	ft_printf("%d\n",minishell->env_initnb);
}

void	display_prompt(void)
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

int		main(int ac, char **av, char **env)
{
	t_minishell minishell;

	welcome_shell();
	minishell.env_list = (t_env *)malloc(sizeof(t_env));
	init_env(env, &minishell, minishell.env_list);
	minishell.path = getcwd(NULL, 0);
	while (1)
	{
		display_prompt();
		signal(SIGINT, parent_signal_handler); //Ctrl+C Ctrl+\ 수행하기
		signal(SIGQUIT, parent_signal_handler); //Ctrl+C Ctrl+\ 수행하기
		cmd_handler(&minishell);		  // stdin 입력을 input에 저장한다.
	}
	return (0);
}