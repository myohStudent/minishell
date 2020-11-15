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
	ft_printf("%d\n",curr->argc);
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

	if (curr->option[0] == '~' && (ft_isspace(curr->option[1]) || curr->option[1] == '/' || curr->option[1] == 0))
	{
		ft_printf("if 1 진입\n");
		curr->option = ft_strjoin(home_dir, curr->option + 1);
		ft_printf("> %s < \n",curr->option);
		//new = ft_strjoin(new, ft_substr(curr->option, i + 1, ft_strlen(curr->option) - i + 1));
		//curr->option = ft_strdup(new);
	}
}

void split_argv(t_cmd *curr)
{
	int i;
	char *temp;
	int len;

	i = 0;
	curr->option = NULL;
	if (!curr || !curr->command || get_argc(curr) == 1)
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
}

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

int parse_cmd(t_minishell *minishell, t_cmd *cmd, char *input)
{
	raw_input = ft_strdup(input); // 전역변수에 백업해서 파이프 나왔을 때 따로 파싱하려고 함 ㅠ
	/*int		start;
	int		i;
	char	*temp;
	start = 0;
	i = 0;
	raw_input = ft_split(input, ';');
	while (raw_input[start])
	{
		temp = parse_space(raw_input[i], " ");
		if (!temp || !(*temp))
		{
			i = 1;
			raw_input[i] = 0;
		}
		if (i == 0)
			raw_input[i] = temp;	
		start++;
	}
	if (i)
	{
		free(input);
		return (0);
	}
	free(input);
	i = 0;
	while (raw_input[i])
		ft_printf("%s||", raw_input[i++]);
	ft_printf("\n");
	return (1);*/

	int start = 0;
	int end = 0;

	if (!input)
		return (0);
	while (input[end] && end < ft_strlen(input))
	{
		start = end;
		while (input[end] && input[end] != ';')
			end++;
		if (input[end] == ';' || !input[end])
		{
			cmd->next = create_node(minishell, input + start, end - start - 1);
			ft_printf("argc = %d\n",cmd->argc);
			cmd = cmd->next;
		}
		end++;
	}
	return (1);
}
