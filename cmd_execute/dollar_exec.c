#include "../minishell.h"


//g_command_nb에 명령어의 반환값을 넣는 법을 모르겠습니다.
//그 밖에 환경변수를 실행하는 건 작업했습니다.
//쌍따옴표할 시 이 함수를 불러야 합니다.

int		dollar_exec(t_cmd *curr, t_minishell *minishell)
{
	t_env *env;
	int i;
	char	*temp;
	t_cmd *envcmd;


	env = minishell->env_list;
	i = 0;
	if (curr->hasquote == 1)
	{
		ft_printf("<<<<<<<<<<<<%d>>>>>>>>>>>>>",curr->hasquote);
		return (0);
	}
	if (curr->command[0] == '$' && curr->command[1] == '?')
	{
		ft_putstr_fd(ft_itoa(g_command_nb), 1);
		ft_putstr_fd(": command not found\n", 1);
		g_command_nb = 127;
		return (1);
	}
	else if (curr->command[0] == '$') //&& curr->command[1] == '?' && curr->option)
	{
		if (curr->option) // $asdf pwd 일 때 뒷 옵션이 명령어로 인식되어 수행된다, pipe불가
		{
			temp = ft_strdup(curr->option);
			free(curr->command);
			free(curr->option);
			curr->option = NULL;
			while (temp[i] && temp[i] != ' ')
				i++;
			if (i == ft_strlen(temp))
				curr->command = ft_strdup(temp);
			else
			{
				curr->command = ft_substr(temp, 0, i);
				while (temp[i])
				{
					if (temp[i] == ' ')
					{
						curr->option = ft_substr(temp, i + 1, ft_strlen(temp));
						break ;
					}
					i++;
				}
			}
			ft_printf("curr->command:/%s/ curr->option:/%s/\n", curr->command, curr->option);
			free(temp);
		}
		else
		{
			i = 0;
			while (env && i < minishell->env_currnb)
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
	}
	return (0);
}


int		dollar_exec_with_quote(t_cmd *curr, t_minishell *minishell)
{
	t_env *env;
	int i;
	char	*temp;
	t_cmd *envcmd;


	env = minishell->env_list;
	i = 0;
	ft_printf("dollar exec with quote 들어옴 LOL \n");
	return (0);
	if (curr->hasquote == 1)
		return (0);
	if (curr->command[0] == '$' && curr->command[1] == '?')
	{
		ft_putstr_fd(ft_itoa(g_command_nb), 1);
		ft_putstr_fd(": command not found\n", 1);
		g_command_nb = 127;
		return (1);
	}
	else if (curr->command[0] == '$') //&& curr->command[1] == '?' && curr->option)
	{
		if (curr->option) // $asdf pwd 일 때 뒷 옵션이 명령어로 인식되어 수행된다, pipe불가
		{
			temp = ft_strdup(curr->option);
			free(curr->command);
			free(curr->option);
			curr->option = NULL;
			while (temp[i] && temp[i] != ' ')
				i++;
			if (i == ft_strlen(temp))
				curr->command = ft_strdup(temp);
			else
			{
				curr->command = ft_substr(temp, 0, i);
				while (temp[i])
				{
					if (temp[i] == ' ')
					{
						curr->option = ft_substr(temp, i + 1, ft_strlen(temp));
						break ;
					}
					i++;
				}
			}
			//ft_printf("curr->command:/%s/ curr->option:/%s/\n", curr->command, curr->option);
			free(temp);
		}
	}
	return (0);
}