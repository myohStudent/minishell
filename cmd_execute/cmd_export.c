#include "../minishell.h"

void copy_env(t_minishell *minishell, t_env *export_list, t_env *env)
{
	if (env == NULL)
		return ;
	minishell->env_currnb = 0;
	while (env)
	{
		export_list->next = (t_env *)malloc(sizeof(t_env));
		export_list->variable = ft_strdup(env->variable);
		export_list->value = ft_strdup(env->value);
		minishell->env_currnb++;
		export_list = export_list->next;
		env = env->next;
	}
}

int			    ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void sort_env(t_minishell *minishell, t_env *export_list)
{
	t_env	*export1;
	t_env	*export2;
	t_env	*next;

	export1 = minishell->export_list;
	int i = 0;
	while (export1)
	{
		export2 = export_list;
		while (export2->next)
		{
			if (ft_strcmp(export2->variable, export2->next->variable) > 0)
			{ //여기에다 가져온 함수에 원하는 인자를 넣어서 실행한다. ft_strcmp와 동일한 형태로 생각하고 결과값은 int가 된다.
				next = export2;
				export2 = export2->next;
				export2->next = next;
			}
			export2 = export2->next;
		}
		export1 = export1->next;
		ft_printf("%d",i);
	}
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
		minishell->export_list = (t_env *)malloc(sizeof(t_env));

		copy_env(minishell, minishell->export_list, minishell->env_list);
		ft_printf("----------------------------절취선 \n");
		sort_env(minishell, minishell->export_list);
		print_env(minishell->export_list);
		ft_printf("----------------------------절취선 \n");
	}

	if (curr->argc == 0)
		print_env(minishell->export_list);
	/*if (curr->argc > 1)
	{
		new_env = ft_split(curr->option, ' ');
		while(str)
		{
			split_new_env = ft_split(*str, '=');
			if (!(ft_strncmp 써서 minishell->export_list 에 curr->option의 앞부분과 일치하는 변수가 있는지 판별하고 치환하는 함수))
			{
				envadd_back(minishell->export_list, split_new_env);
				envadd_back(minishell->env_list, split_new_env);
			}
			str++;
			free_arr(split_new_env);
		}
		free_arr(new_env);
	}*/
	return (1);
}