/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 02:55:05 by seohchoi          #+#    #+#             */
/*   Updated: 2020/12/14 15:21:50 by myoh             ###   ########.fr       */
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
// void	shell_levelup(t_minishell *minishell, t_env *env_list)
// {
// 	int		i;
// 	t_env	*list;

// 	i = 0;
// 	list = env_list;
// 	while (list && i < minishell->env_currnb)
// 	{
// 		if (ft_strcmp(list->variable, "SHLVL") == 0)
// 		{
// 			list->value++; //아니 문자열이네 이거 이러면 안 되잖아 다시 만들어야 함 ㅠㅠ
// 			break ;
// 		}
// 		list = list->next;
// 		i++;
// 	}
// }

int		main(int ac, char **av, char **env)
{
	t_minishell minishell;

	welcome_shell();
	minishell.env_list = (t_env *)malloc(sizeof(t_env));
	init_env(env, &minishell, minishell.env_list);
	get_path(minishell.env_list, &minishell);
	get_envp(env, minishell.env_currnb);
	//shell_levelup(&minishell, minishell.env_list); //셸레벨 올리기 필요없음
	minishell.path = getcwd(NULL, 0);
	signal(SIGINT, parent_signal_handler); //Ctrl+C Ctrl+\ 수행하기
	signal(SIGQUIT, parent_signal_handler); //Ctrl+C Ctrl+\ 수행하기
	while (1)
	{
		display_prompt();
		cmd_handler(&minishell);		  // stdin 입력을 input에 저장한다.
	}
	minishell.environ = NULL;
	return (0);
}