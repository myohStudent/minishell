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

void tild_handler(t_minishell *minishell, t_cmd *curr)
{
	if (curr->option[0] == '~' && (ft_isspace(curr->option[1]) || curr->option[1] == '/' || curr->option[1] == 0))
		curr->option = ft_strjoin(g_home_dir, curr->option + 1);
}

void split_argv(t_cmd *curr)
{
	int i;
	char *temp;
	int len;

	i = 0;
	curr->option = NULL;
	if (!curr || !curr->command || (get_argc(curr) == 1 && curr->hasquote == 0))
		return;
	if (ft_isquote(curr->command[0]) && has_quotes(curr->command) && curr->command[has_quotes(curr->command)] != ' ')
		i = has_quotes(curr->command);
	i -= ft_remove_quote(curr);
	// ft_printf("i ------------- %d, type %d  str %s\n", i, curr->quote_type,curr->command);
	if (i < 0)
		i = 0;
	// curr->quote_type == 2 || curr->quote_type == 1)
	// ft_printf("i ------------- %d, type %d \n", i, curr->quote_type);
	while (!(ft_isspace(curr->command[i])) && curr->command[i])
		i++;
	//ft_printf("i ------------- %d, type %d \n", i, curr->quote_type);
	//ft_printf("len : %d  str : %s\n",ft_strlen(curr->command), curr->command);
	len = ft_strlen(curr->command);
	temp = ft_substr(curr->command, 0, i);
	// ft_printf(">>%s<<\n", temp);
	// ft_printf("%d, %d, %d, %d \n", i + 1, ft_strlen(curr->command), (ft_strlen(curr->command) - i), len);
	//ft_printf("len : %d  str : %s\n",ft_strlen(curr->command), curr->command);
	curr->option = ft_substr(curr->command, i + 1, len - (i + 1));
	// ft_printf(">>%s<<\n", curr->option);

	//이부분 free 오류
	free(curr->command);
	curr->command = ft_strdup(temp);
	//이부분 free 오류
	free(temp);
	temp = 0;
	// ft_printf("cmd:%s, opt:%s, argc:%d|\n", curr->command, curr->option, curr->argc);
}

char *check_copy(char const *s, unsigned int start, size_t len)
{
	char *a;
	int i;

	i = 0;
	if (!(a = (char *)malloc(sizeof(char) * ((int)len))))
		return (NULL);
	while (i < (int)len)
	{
		a[i] = s[(int)start];
		i++;
		start++;
	}
	a[i] = '\0';
	ft_printf("%d, %s))\n", i, a);
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
	new->command = ft_substr(data, word_start, word_end - word_start + 1);
	get_quote_type(new);
	if (ft_isquote(new->command[0]) && has_quotes(new))
	{
		ft_printf("커맨드가 쿼트일 경우'%d, %d'\n",new->hasenv, new->quote_type);
		new->argc = 0;
		if(new->hasenv == 1 && new->quote_type != 1)
			dollar_exec_with_quote(new, minishell); //세그폴트남
		split_argv_quotes_cmd(new);
	}
	else
	{
		if(new->hasenv == 1 & new->quote_type != 1)
			dollar_exec_with_quote(new, minishell); //세그폴트남
		ft_printf("커맨드가 쿼트가 아닐 경우'%d, %d'\n",new->hasenv, new->quote_type);
		split_argv(new);
	}
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
	new->hasquote = 0;
	new->hasenv = 0;
	new->quote_type = 0;
	set_node(minishell, new, data, word_len);
	new->next = 0;
	return (new);
}

int parse_cmd(t_minishell *minishell, t_cmd *cmd, char *input)
{
	g_input = ft_strdup(input);

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
			ft_printf("argc = %d\n", cmd->argc);
			cmd = cmd->next;
		}
		end++;
	}
	return (1);
}