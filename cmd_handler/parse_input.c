#include "../minishell.h"

int get_argc(t_cmd *curr)
{
	int i;
	int ac;

	i = 0;
	while (curr->command[i])
	{
		if (ft_isspace(curr->command[i]))
			curr->argc++;
		i++;
	}
	i--;
	while (ft_isspace(curr->command[i]))
	{
		curr->argc--;
		i--;
	}
	curr->argc++;
	return (curr->argc);
}

char				*parse_search(char *s, int c)
{
	unsigned char	s2;
	int				i;

	s2 = (unsigned char)c;
	i = 0;
	while (s[i] != s2 && s && s[i])
		i++;
	if (s[i] == s2)
		return (&s[i]);
	return (0);
}

void				tild_handler(t_minishell *minishell, t_cmd *curr)
{
	int i;
	char *home;

	if (curr->option[0] == '~' && (ft_isspace(curr->option[1]) || curr->option[1] == '/' || curr->option[1] == 0))
	{
		ft_printf("if 1 진입\n");
		ft_printf("%d\n",env_index(minishell, "home\0"));
		home = ft_strdup(minishell->env_set[env_index(minishell, "home\0")]);
		ft_printf("home : %s\n",home);
		curr->option = ft_strjoin(home, curr->option + 1);
		ft_printf("> %s < \n",curr->option);
		//new = ft_strjoin(new, ft_substr(curr->option, i + 1, ft_strlen(curr->option) - i + 1));
		//curr->option = ft_strdup(new);
		free (home);
	}
}

void split_argv(t_cmd *curr)
{
	int i;
	char *temp;
	int len;

	i = 0;
	curr->option = NULL;
	/*if (!curr || !curr->command || get_argc(curr) == 1)
		return ;*/
	// 이유도 모르겠는데 여기서 opt: 0일 때 세그폴트가 뜨네요 그래서 +1한 상태예요ㅠㅠㅠ
	if (!curr || !curr->command || get_argc(curr) + 1 == 1)
		return ;
	i = 0;
	while (!(ft_isspace(curr->command[i])) && curr->command[i])
		i++;
	//ft_printf("len : %d  str : %s\n",ft_strlen(curr->command), curr->command);
	len = ft_strlen(curr->command);
	temp = ft_substr(curr->command, 0, i);
	ft_printf(">>%s<<\n", temp);
	ft_printf("%d, %d, %d, %d \n", i + 1, ft_strlen(curr->command), (ft_strlen(curr->command) - i), len);
	//ft_printf("len : %d  str : %s\n",ft_strlen(curr->command), curr->command);
	curr->option = ft_substr(curr->command, i + 1, len - (i + 1));
	ft_printf(">>%s<<\n", curr->option);
	free(curr->command);
	curr->command = ft_strdup(temp);
	free(temp);
	temp = 0;
	ft_printf("cmd:%s, opt:%s, argc:%d|\n", curr->command, curr->option, curr->argc);

}
/*
char		*check_copy(char const *s, unsigned int start, size_t len)
{
	char	*a;
	int		i;

	i = 0;
	if (!(a = (char *)malloc(sizeof(char) * ((int)len))))
	{
		ft_printf("리턴널 일어남\n");
		return (NULL);	
	}
	ft_printf("((%d, %d, ", start, len);
	while (i < (int)len)
	{
		a[i] = s[(int)start];
		i++;
		start++;
	}
	a[i] = '\0';
	ft_printf("%d, %s))\n",i, a);
	return (a);
}*/

void set_node(t_minishell *minishell, t_cmd *new, char *data, int word_end)
{
	int word_start;

	word_start = 0;
	while (ft_isspace(data[word_start]))
		word_start++;
	while (ft_isspace(data[word_end]) || data[word_end] == ';')
		word_end--;
	//word_end++;
	printf("(%d %d)\n", word_start, word_end - word_start);
	new->command = ft_substr(data, word_start, word_end - word_start + 1);
	//ft_printf("%c",new->command[ft_strlen(new->command)]);
	//ft_printf("---------------------\n");
	//ft_printf(">>%s<<\n", new->command);
	//ft_printf("%s, %d, %d \n",new->command, (ft_strlen(new->command), word_end - word_start));
	split_argv(new);
	//if (new->option != NULL && new->option)
		//tild_handler(minishell, new);
	if (new->option != NULL && new->option)
		tild_handler(minishell, new);
}

t_cmd *create_node(t_minishell *minishell, char *data, int word_len)
{
    t_cmd *new;
	int i;

	i = 0;
    if (!(new = (t_cmd *)malloc(sizeof(t_cmd))))
         return (NULL);
	set_node(minishell, new, data, word_len);
    new->next = 0;
    return (new);
}

void parse_cmd(t_minishell *minishell, t_cmd *cmd, char *input)
{
	int start = 0;
	int end = 0;

	if (!input)
		return ;
	while (input[end] && end < ft_strlen(input))
	{
		start = end;
		while (input[end] && input[end] != ';')
			end++;
		if (input[end] == ';' || !input[end])
		{
			cmd->next = create_node(minishell, input + start, end - start - 1);
			cmd = cmd->next;
		}
		end++;
	}
}
