#include "../libft/libft.h"
#include "../minishell.h"

/*
void get_argc(t_minishell *minishell, char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			minishell->cmd.argc++;
		i++;
	}
	i--;
	while (ft_isspace(input[i]))
	{
		minishell->cmd.argc--;
		i--;
	}
	minishell->cmd.argc++;
}

void split_command(t_minishell *minishell, char *input, int word_len, int i)
{
	int j;

	j = 0;
	while (j < word_len)
	{
		minishell->cmd.command[i][j] = input[j];
		j++;
	}
	minishell->cmd.command[i][j] = 0;
}

void split_input(t_minishell *minishell, char *input)
{
	int j;
	int i;
	int k;
	
	i = 0;
	k = 0;
	while (input[k] && i < minishell->cmd.argc)
	{
		j = k;
		while (!(ft_isspace(input[k])) && input[k])
			k++;
		minishell->cmd.command[i] = (char *)malloc(sizeof(char) * ((k - j) + 1));
		//printf("(%c)",input[k]);
		split_command(minishell, input + j, k - j, i);
		//printf("(%s)\n",minishell->cmd.command[i]);
		k++;
		i++;
	}
	//printf("(%d %d)\n",minishell->cmd.argc, i);
}

void parse_input(t_minishell *minishell, char *input)
{
	//get_argc(minishell, input);
	minishell->cmd.command = (char **)malloc(sizeof(char *) * (minishell->cmd.argc + 1));
	split_input(minishell,input);
	minishell->cmd.command[minishell->cmd.argc] = 0;
	//printf("\nargc : %d\n",minishell->cmd.argc);
	//printf("\n-------------------------\n");
}
*/