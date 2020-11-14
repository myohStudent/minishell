#include "../minishell.h"

void copy_env(t_minishell *minishell, t_env *export_list, t_env *env)
{
	if (env == NULL)
		return (-1);
	minishell->env_currnb = 0;
	export_list = (t_env *)malloc(sizeof(t_env));
	while (env)
	{
		export_list->next = (t_env *)malloc(sizeof(t_env));
		export_list->variable = ft_strdup(env->variable);
		export_list->value = ft_strdup(env->value);
		minishell->env_currnb++;
		export_list = >export_list->next;
		env = env->next;
	}
}

void sort_env(t_minishell *minishell, t_env *export_list)
{

}

void envadd_back(t_env *list, char **newenv)
{

}

int cmd_export(t_cmd *curr, t_minishell *minishell)
{
	char **new_env;
	char **split_new_env;

	if(!minishell->export_list)
	{
		copy_env(minishell, minishell->export_list, minishell->env_list);
		sort_env(minishell, export_list);
	}
	if (curr->argc == 0)
		print_env(minishell->export_list);
	if (curr->argc > 1)
	{
		new_env = ft_split(curr->option, ' ');
		while(str)
		{
			split_new_env = ft_split(*str, '=');
			if (!(ft_strncmp 써서 minishell->export_list 에 curr->option의 앞부분과 일치하는 변수가 있는지판별하고 치환하는 함수))
			{
				envadd_back(minishell->export_list, split_new_env);
				envadd_back(minishell->env_list, split_new_env);
			}
			str++;
			free_arr(split_new_env);
		}
		free_arr(new_env);
	}

}