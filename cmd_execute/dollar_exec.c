#include "../minishell.h"


//g_command_nb에 명령어의 반환값을 넣는 법을 모르겠습니다.
//그 밖에 환경변수를 실행하는 건 작업했습니다.
//쌍따옴표할 시 이 함수를 불러야 합니다.

int		dollar_exec(t_cmd *curr, t_minishell *minishell)
{
	t_env *env;
	int i;
	int j;
	char	*temp;
	t_cmd *envcmd;
	int hasargc = 0;

	env = minishell->env_list;
	i = 0;
	ft_printf("curr->hasquote == %d && curr->hasenv == %d) || curr->quote_type == %d\n ",curr->hasquote, curr->hasenv, curr->quote_type);
	if ((curr->hasquote == 1 && curr->hasenv == 0) || curr->quote_type == 1 )
		return (0);
	ft_printf("env > curr > %s\n",curr->command);
	while (curr->command[i] != '$' && curr->command[i])
		i++;
	if (!curr->command[i])
		return (0);
	if (curr->command[i] == '$' && curr->command[i + 1] == '?')
	{
		ft_putstr_fd(ft_itoa(g_command_nb), 1);
		ft_putstr_fd(": command not found\n", 1);
		g_command_nb = 127;
		return (1);
	}
	else if (curr->command[i] == '$') //&& curr->command[1] == '?' && curr->option)
	{
		j = 0;
		while (env && j < minishell->env_currnb)
		{
			/*
			if (ft_strcmp(env->variable, curr->command + i + 1) == 0)
			{
				envcmd = (t_cmd *)malloc(sizeof(t_cmd));
				if (i != 0)
					envcmd->command = ft_strjoin(ft_substr(curr->command, 0, i), env->value);
				else
					envcmd->command = ft_strdup(env->value);	
			*/
			if (ft_strncmp(env->variable, curr->command + i + 1, ft_strlen(curr->command) - i - 1) == 0)
			{
				envcmd = (t_cmd *)malloc(sizeof(t_cmd));
				// if (i != 0)
				// 	envcmd->command = ft_strjoin(ft_substr(curr->command, 0, i), env->value);
				if (i != 0)
					envcmd->command = ft_strjoin(ft_substr(curr->command, 0, i), env->value);
				else 
					envcmd->command = ft_strdup(env->value);
				///////////
				envcmd->argc = 1;
				hasargc = envcmd->argc;
				exec_else(minishell, envcmd);
				free(envcmd);
				return (1);
			}
			j++;
			env = env->next;
		}
		if (!hasargc)
		{
			ft_printf("----------------------\n");
			envcmd = (t_cmd *)malloc(sizeof(t_cmd));
			envcmd->command = ft_substr(curr->command, 0, i);
			exec_else(minishell, envcmd);
			free(envcmd);
			return (1);
		}
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
	}
	return (0);
}

int get_next_space(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (i);
		i++;
	}
	return (get_first_quote(str, 2));
}

int		dollar_exec_with_quote(t_cmd *curr, t_minishell *minishell)
{
	t_env *env;
	int i;
	int j;
	int envindex;
	char	*temp;

	i = 0;
	env = minishell->env_list;
	while (curr->command[i] != '$' && curr->command[i])
		i++;
	if (!curr->command[i])
		return (0);
	ft_printf(">>>>>>>>>>exec with quote<<<<<<<<<<\n");
	// "$HOME asdf"
	j = get_next_space(curr->command + i);
	ft_printf("[%d　%d]\n",i, j);

	if (curr->command[i] == '$' && curr->command[i + 1] == '?')
	{
		ft_putstr_fd(ft_itoa(g_command_nb), 1);
		ft_putstr_fd(": command not found\n", 1);
		g_command_nb = 127;
		return (1);
	}
	else if (curr->command[i] == '$') //&& curr->command[1] == '?' && curr->option)
	{
		envindex = 0;
		while (env && envindex < minishell->env_currnb)
		{
			ft_printf("[%s %d : %c %c]\n",env->variable, envindex, curr->command[i + 1], curr->command[j - 1]);

			if (ft_strncmp(env->variable, curr->command + i + 1, j - 1) == 0)
			{
				char *startstr;
				// if (i != 0)
				// 	envcmd->command = ft_strjoin(ft_substr(curr->command, 0, i), env->value);
				// asdf"$HOME"; "$HOME asdf"; asdfasdf"$HOME";

				temp = ft_substr(curr->command, 0, i);
				startstr = ft_strjoin(temp, env->value);
				free(temp);
				temp = ft_substr(curr->command, j + i, ft_strlen(curr->command) - (j + i) );
				ft_printf("))))))%s(((((\n",temp);
				free(curr->command);
				curr->command = ft_strjoin(startstr, temp);
				free(temp);
				break;
				// curr->command + i + ft_strlen(env->variable) + 1);

				// envcmd->command = ft_strdup(env->value);		
				
			}
			
			envindex++;
			env = env->next;
		}
		ft_printf(">>>>>>>>exec command<<<<<< %s\n",curr->command);
	}

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
		ft_printf("curr->command:/%s/ curr->option:/%s/\n", curr->command, curr->option);

	//asdf"$HOME"; "asfd$HOME"; asdf"$HOME"asdf; "$HOME"asdf 의 경우 핸들링해야한다.
	//그러나 asdf$HOMEasdf, $HOMEasdf 의 경우 핸들링하지 말아야한다.(그냥 dollor exec으로 넘어가게해야함)

	//dollor exec을 그대로 붙여넣되
	
//를 포함해야한다.
// 이것은 asdf"$HOME"asdf를 핸들링해준다.

}