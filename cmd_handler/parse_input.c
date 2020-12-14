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
	ft_printf("%d\n", curr->argc);
	return (curr->argc);
}

void tild_handler(t_minishell *minishell, t_cmd *curr)
{
	int i;

	if (curr->option[0] == '~' && (ft_isspace(curr->option[1]) || curr->option[1] == '/' || curr->option[1] == 0))
	{
		ft_printf("if 1 진입\n");
		curr->option = ft_strjoin(home_dir, curr->option + 1);
		ft_printf("> %s < \n", curr->option);
		//new = ft_strjoin(new, ft_substr(curr->option, i + 1, ft_strlen(curr->option) - i + 1));
		//curr->option = ft_strdup(new);
	}
}

int ft_remove_quote(t_cmd *curr)
{
	char *temp;
	int quotenum;
	int i;

	quotenum = 0;
	i = 0;
	while (curr->command[i])
	{
		if (ft_isquote(curr->command[i]) == 1)
			quotenum++;
		i++;
	}
	temp = ft_strdup(curr->command);
	free(curr->command);
	curr->command = ft_trimchar(temp, '\'');
	free(temp);
	temp = ft_trimchar(curr->command, '\"');
	free(curr->command);
	curr->command = temp;
	return (quotenum);
}

void split_argv(t_cmd *curr)
{
	int i;
	char *temp;
	int len;

	i = 0;
	curr->option = NULL;
	if ((!curr || !curr->command || get_argc(curr) == 1) && !has_quotes(curr->command))
		return;
	if (ft_isquote(curr->command[0]) && has_quotes(curr->command) && curr->command[has_quotes(curr->command)] != ' ')
		i = has_quotes(curr->command);
	i -= ft_remove_quote(curr);
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

char *check_copy(char const *s, unsigned int start, size_t len)
{
	char *a;
	int i;

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
	ft_printf("%d, %s))\n", i, a);
	return (a);
}

void split_argv_quotes_cmd(t_cmd *curr)
{
	int i;
	char *temp;
	int len;

	i = 0;
	curr->option = NULL;
	if ((!curr || !curr->command || get_argc(curr) == 1) && !has_quotes(curr->command))
		return;
	i = has_quotes(curr->command) - ft_remove_quote(curr);
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

void set_node(t_minishell *minishell, t_cmd *new, char *data, int word_end)
{
	int word_start;

	word_start = 0;
	while (ft_isspace(data[word_start]))
		word_start++;
	while (ft_isspace(data[word_end]) || data[word_end] == ';')
		word_end--;
	//word_end++;
	//printf("(%d %d)\n", word_start, word_end - word_start);
	new->command = ft_substr(data, word_start, word_end - word_start + 1);
	//ft_printf("%c",new->command[ft_strlen(new->command)]);
	//ft_printf("---------------------\n");

	//has_quotes에서 "가 2개 있고, 첫번 째 "앞에  '이 하나라도 없다면
	//무조건 has_env 스위치 켜지도록 한다.
	// hasenv==1이고 "하고 str[1]이 $이면 ENV와 strcmp해서 ==0인경우 ENV로 치환. ==0이 아니면 ENV로 치환하지않음.

	//quotes가 "ㄴㅁㅁㄴㄹㅇ'$HOME'ㅁㄴㅇㄹㅁㄹ" 인 경우 무시하고 환경변수로 치환해도됨.
	//아무 종류의 쿼트가 존재하고, 그 앞에 다른 종류의 쿼트가 존재한다면, 안쪽에 있는 종류의 쿼트는 보존해야함.

		new->hasenv = 0;

	if (ft_isquote(new->command[0]) && has_quotes(new) &&
		(new->command[has_quotes(new)] == 0 ||
		 new->command[has_quotes(new)] == ' '))
		split_argv_quotes_cmd(new);
	else
		ft_printf("dtd");
	// split_argv(new);

	//ft_printf("%s, %d, %d \n",new->command, (ft_strlen(new->command), word_end - word_start));
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
	raw_input = ft_strdup(input);
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
			ft_printf("argc = %d\n", cmd->argc);
			cmd = cmd->next;
		}
		end++;
	}
	return (1);
}