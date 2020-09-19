#include "./libft/libft.h"
#include "./minishell.h"

void get_argc(t_minishell *minishell, char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			minishell->input.argc++;
		i++;
	}
	minishell->input.argc++;
}

void split_argv(t_minishell *minishell, char *input, int word_len, int i)
{
	int j;

	j = 0;
	while (j < word_len)
	{
		minishell->input.argv[i][j] = input[j];
		j++;
	}
	minishell->input.argv[i][j] = 0;
}

void split_input(t_minishell *minishell, char *input)
{
	int j;
	int i;
	int k;
	
	i = 0;
	k = 0;
	while (input[k])
	{
		j = k;
		while (!(ft_isspace(input[k])) && input[k])
			k++;
		minishell->input.argv[i] = (char *)malloc(sizeof(char) * ((k - j) + 1));
		//printf("(%c)",input[k]);
		//printf("(%d)",j);
		split_argv(minishell, input + j, k - j, i);
		k++;
		i++;
	}
}

void parse_input(t_minishell *minishell, char *input)
{
	get_argc(minishell, input);
	minishell->input.argv = (char **)malloc(sizeof(char *) * (minishell->input.argc + 1));
	split_input(minishell,input);
	minishell->input.argv[minishell->input.argc] = 0;
	//printf("\nargc : %d\n",minishell->input.argc);
	//printf("\n-------------------------\n");
}