#include "../minishell.h"

int ft_isquote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int get_first_quote(char *command, int type)
{
	int i;

	i = 0;
	if (type != 1 && type != 2)
		return (-1);
	while (command[i])
	{
		if (ft_isquote(command[i]) == type) //34
			return (i);
		// ft_printf("> %d", i);
		i++;
	}
	return (-1);
}

int has_quotes(t_cmd *new)
{
	int isdouble;
	int isquote;
	int i;

	isdouble = 0;
	isquote = 0;
	i = 0;
	while (new->command[i])
	{
		if (new->quote_type != 2) //싱글쿼트가 안쪽에있는게 아닐경우
			if (ft_isquote(new->command[i]) == 1) //34
				isquote++;
		if (new->quote_type != 1)
			if (ft_isquote(new->command[i]) == 2) //39
				isdouble++;
		i++;
		if (isquote == 2 || isdouble == 2)
			return (i);
	}
	return (0);
}

int get_quote_type(t_cmd *new)
{
	int isdouble;
	int isquote;
	int i;

	isdouble = 0;
	isquote = 0;
	i = 0;
	while (new->command[i])
	{
		if (ft_isquote(new->command[i]) == 1) //34
			isquote++;
		if (ft_isquote(new->command[i]) == 2) //39
			isdouble++;
		i++;
		if (isdouble == 2 && ((get_first_quote(new->command, 1) <
		get_first_quote(new->command, 2)) || !get_first_quote(new->command, 1))) //'이 없거나, 있어도 "보다 늦게 나온다.
			new->hasenv = 1;//env가 있다
		if (isdouble == 2 && 
		get_first_quote(new->command, 1) > -1 && //문제시 이거 주석처리할것
		get_first_quote(new->command, 1) <
		get_first_quote(new->command, 2))
			new->quote_type = 1; //더블쿼트 지우면 안된다는 표시
		if (isquote == 2 && 
		get_first_quote(new->command, 2) > -1 && //문제시 이거 주석처리할것
		get_first_quote(new->command, 1) > get_first_quote(new->command, 2))
		{
			new->quote_type = 2; //싱글쿼트 지우면 안된다는 표시
			new->hasenv = 1;//env가 있다
		}
		if (isquote == 2 || isdouble == 2)
		{
			new->hasquote = 1;
			return (i);
		}	
	}
	new->hasquote = 0;
	return (0);
}