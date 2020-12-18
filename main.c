/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 02:55:05 by seohchoi          #+#    #+#             */
/*   Updated: 2020/12/19 00:46:16 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./minishell.h"

void		init_env(char **env, t_minishell *minishell, t_env *env_list)
{
	int		i;
	char	**str;

	i = 0;
	minishell->env_currnb = 0;
	while (env[i])
	{
		str = ft_split(env[i], '='); // split해서 나눠 놓기
		if (ft_strncmp(str[0], "HOME\0", 5) == 0)
			home_dir = ft_strdup(str[1]);
		env_list->variable = ft_strdup(str[0]);
		env_list->value = ft_strdup(str[1]);

		if (env[i + 1])
		{
			env_list->next = (t_env *)malloc(sizeof(t_env));
			env_list = env_list->next;	
		}
		free_arr(str);
		minishell->env_currnb++;
		i++;
	}
	env_list->next = NULL;
	ft_printf("%d\n",minishell->env_currnb);
}


void get_path(t_env *list, t_minishell *minishell)
{
	char	**bin;
	char *temp;
	int i;
	t_env *l;

	l = list;
	i = 0;
	temp = NULL;
	while (l && i < minishell->env_currnb)
	{
		if (ft_strcmp(l->variable, "PATH") == 0)
		{
			temp = ft_strdup(l->value);
			break ;
		}
		l = l->next;
		i++;
	}
	if (temp)
	{
		bin = ft_split(temp, ':');
		free(temp);
	}
	i = 0;
	while (bin[i])
		i++;
	pipe_bin = NULL;
	pipe_bin = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (bin && bin[i])
	{
		pipe_bin[i] = ft_strjoin(bin[i], "/");
		free(bin[i]);
		i++;
	}
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

void	get_envp(char **env, int i)
{
	int 	j;

	j = 0;
	envp_list = (char **)malloc(sizeof(char *) * i);
	while (j < i)
	{
		envp_list[j] = ft_strdup(env[j]);
		j++;
	}
	envp_list[j] = NULL;
}

int		main(int ac, char **av, char **env)
{
	t_minishell minishell;

	welcome_shell();
	minishell.env_list = (t_env *)malloc(sizeof(t_env));
	init_env(env, &minishell, minishell.env_list);
	get_path(minishell.env_list, &minishell);
	get_envp(env, minishell.env_currnb);
	g_sigexit = 0;
	minishell.path = getcwd(NULL, 0);
	while (1)
	{
		display_prompt();
		signal(SIGINT, parent_signal_handler);
		signal(SIGQUIT, parent_signal_handler);
		if (g_sigexit != 1 && g_sigexit != 2)
			cmd_handler(&minishell);// stdin 입력을 input에 저장한다.
	}
	//////////////free////////////////
	clear_env(minishell.env_list);
	free_arr(envp_list);
	free(minishell.path);
	free(home_dir);
	free(raw_input);
	return (0);
}