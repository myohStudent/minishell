#include "../minishell.h"

int get_argc(t_cmd *curr)
{
	int i;

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

*char				*parse_search(char *s, int c)
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

void split_argv(t_cmd *curr)
{
	int i;
	char *temp;

	i = 0;
	if (!curr || !curr->command || get_argc(curr) == 1)
		return ;
	while (!(ft_isspace(curr->command[i])) && curr->command[i])
		i++;
	temp = ft_substr(curr->command, 0, i);
	curr->option = ft_substr(curr->command, i + 1, ft_strlen(curr->command));	
	free(curr->command);
	curr->command = ft_strdup(temp);
	free(temp);

	//ㅇㅗㅂ션함수 만드세요.
	
	
	int i = 0;
	while (minishell->env_temp[i])
	{
		if (ft_strncmp(minishell->env_temp[i], "HOME\0", 5) == 0)
			chdir(minishell->env_temp[i + 1]);
		i++;
	}
	if (temp = parse_search(curr->option, ~))
	{
		if (!(temp[1]) || ft_isspace(temp[1]))
			temp[1] = 
		else
		{
			temp[0] = '\0';
			curr->option = ft_strjoin(curr->option, temp[1]);
		}
		
	}
	//printf("cmd:%s, opt:%s, argc:%d|\n", curr->command, curr->option, curr->argc);

}

void set_node(t_cmd *new, char *data, int word_end)
{
	int word_start;

	word_start = 0;
	while (ft_isspace(data[word_start]))
		word_start++;
	while (ft_isspace(data[word_end]) || data[word_end] == ';')
		word_end--;
	word_end++;
	//printf("(%d %d)\n", word_start, word_end);
	new->command = ft_substr(data, word_start, word_end - word_start);
	split_argv(new);
}

t_cmd *create_node(char *data, int word_len)
{
    t_cmd *new;
	int i;

	i = 0;
    if (!(new = (t_cmd *)malloc(sizeof(t_cmd))))
         return (NULL);
	set_node(new, data, word_len);
    new->next = NULL;
    return (new);
}

void parse_cmd(t_cmd *cmd, char *input)
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
			cmd->next = create_node(input + start, end - start - 1);
			cmd = cmd->next;
		}
		end++;
	}
}