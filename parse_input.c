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
}

void split_argv(t_minishell *minishell, char *input, int i, int j)
{
	int k;

	k = 0;
	while (k < j)
	{
		minishell->input.argv[i][k] = input[k];
		k++;
	}
	minishell->input.argv[i][k] = 0;
}

void split_input(t_minishell *minishell, char *input)
{
	int j;
	int i;
	
	i = 0;
	j = 0;
	while (*input)
	{
		j = 0;
		while (!(ft_isspace(*input)))
		{
			input++;
			j++;
		}
		minishell->input.argv[i] = (char *)malloc(sizeof(char) * (j + 1));
		split_argv(minishell, input, i, j);
		i++;
	}
}

void parse_input(t_minishell *minishell, char *input)
{
	get_argc(minishell, input);
	printf("(%d)",minishell->input.argc);
	minishell->input.argv = (char **)malloc(sizeof(char *) * (minishell->input.argc + 1));
	split_input(minishell,input);

	for (int i = 0; minishell->input.argv[i]; i++)
		printf("%s\n", minishell->input.argv[i]);
}