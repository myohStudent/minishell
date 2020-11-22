#include "../minishell.h"


//g_command_nb에 명령어의 반환값을 넣는 법을 모르겠습니다.
//그 밖에 환경변수를 실행하는 건 작업했습니다.
//쌍따옴표할 시 이 함수를 불러야 합니다.

int		dollar_exec(t_cmd *curr, t_minishell *minishell)
{
	t_env *env;
	int i;
	t_cmd *envcmd;


	env = minishell->env_list;
	i = 0;
	if (curr->command[0] == '$' && curr->command[1] == '?')
	{
		ft_putstr_fd(ft_itoa(g_command_nb), 1);
		ft_putstr_fd(": command not found\n", 1);
		return (1);
	}
	else if (curr->command[0] == '$')
	{
		while(env && i < minishell->env_currnb)
		{
			if (ft_strcmp(env->variable, curr->command + 1) == 0)
			{
				envcmd = (t_cmd *)malloc(sizeof(t_cmd));
				envcmd->command = ft_strdup(env->value);
				envcmd->argc = 1;
				exec_else(minishell, envcmd);
				free(envcmd);
				return (1);
			}
			i++;
			env = env->next;
		}
	}
	return (0);
}

