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
	export_list->next = NULL;
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
	int i;
	int j;
	t_env 	*prev_node;
	t_env 	*curr_node;
	t_env	*next_node;

	i = minishell->env_initnb;
	while (i)
	{
		j = 0;
		curr_node = export_list;
		prev_node = NULL;
		while (j < i && curr_node)
		{
		// ft_printf("%d %d %s\n",i,j,curr_node->variable);
			if (ft_strcmp(curr_node->variable, curr_node->next->variable) > 0)
			{
				next_node = curr_node;
				curr_node = curr_node->next;
				next_node->next = curr_node->next;
				curr_node->next = next_node;
				if (prev_node != NULL)
					prev_node->next = curr_node;
			}
			prev_node = curr_node;
			curr_node = curr_node->next;
			j++;
		}
		i--;
	}
	//print_export(minishell->export_list);

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
		ft_printf("----------------------------절취선1 \n");
		sort_env(minishell, minishell->export_list);
		ft_printf("----------------------------절취선2 \n");
	}
	if (curr->argc == 1)
		//print_export(minishell->export_list);
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
				minishell->env_currnb++;
			}
			str++;
			free_arr(split_new_env);
		}
		free_arr(new_env);
	}*/
	return (1);
}