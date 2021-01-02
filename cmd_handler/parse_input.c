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
	//word_end++;
	//printf("(%d %d)\n", word_start, word_end - word_start);
	new->command = ft_substr(data, word_start, word_end - word_start + 1);
	//ft_printf("%c",new->command[ft_strlen(new->command)]);
	//ft_printf("---------------------\n");

	//has_quotes에서 "가 2개 있고, 첫번 째 "앞에  '이 하나라도 없다면
	//무조건 has_env 스위치 켜지도록 한다.
	//doublequote 앞에 singlequote가 있으면  quote_type = 1
	//singlequote앞에 doublequote가 있을 경우 quote_type = 2
	
	//quote_type ==1일 경우 "" 지우면 안됨
	//quote_type ==2일 경우 ' 지우면 안됨
	
	//그냥 split에서 옵션에서 쿼트 지워주는 함수 만들기
	//'1 2 3 "4 5" 6' 일 경우 버그 
	
	//'12"34"56', "12'34'56", 'asdf"$HOME"asdf' 일 시 '가 안없어지는 버그있음
	//"asdf 'asdf' asdf" 일 경우 안 나옴(나오긴 나오는데 실행값이 0 나옴) 
	//"asdf '$HOME' asdf" 일 경우 안나옴(나오긴 나오는데 실행값이 0 나옴)
	//echo 'ㅁㄴㅇㄹ', echo "asdf" -> remove 쿼트에 진입 안해서 따로 판별값을 줘야될듯
	//--여기까지 완료 --

	//입력값
	//[OK]"asdf 'asdf' asdf"; "$HOME asdf";
	//[OK]echo 'asdf'; echo "asdf"; echo "asdf'asdf'asdf"; echo "asdf 'asdf' asdf"; echo 'asdf"asdf"asdf'; echo 'asdf "asdf" asdf';
	//[OK]asdf"$HOME"; asdf'$HOME'; 'asdf$HOME'; '$HOME asdf'
	//[OK]'12"34"56'; "12'34'56"; 'asdf"$HOME"asdf'; "asfd$HOME"
	//[OK]"$HOMEasdf"; asdf$HOMEasd; 
	//[OK]asdfasdf"$HOME"; '$HOME'asdf;
	//[OK]'asdf "$HOME" asdf';
	//[OK] 'asdf'asdf'asdf'; "asdf"asdf"asdf";
	//[bug] "$HOME"asdf; asdf"$HOME"asdf
	

	//hasenv==1이고, quote_type가 1이 아니고,
	//"하고 str[1]이 $이면 ENV와 strcmp해서 ==0인경우 ENV로 치환. (dollar_exec)
	//quotes가 "ㄴㅁㅁㄴㄹㅇ'$HOME'ㅁㄴㅇㄹㅁㄹ" 인 경우 무시하고 환경변수로 치환해도됨.

	//[bug]'asdf 'asdf' asdf'; "asdf "asdf" asdf"

	//[bug] "asdf '$HOME' asdf"; 
	
	//"asdf'$HOME'asdf"
	
	new->hasquote = 0;
	new->hasenv = 0;
	new->quote_type = 0;
	get_quote_type(new);
	if (ft_isquote(new->command[0]) && has_quotes(new))
	//  && (new->command[has_quotes(new)] == 0 ||
	// 	 new->command[has_quotes(new)] == ' '))
	{
		ft_printf("커맨드가 쿼트일 경우'%d, %d'\n",new->hasenv, new->quote_type);
		new->argc = 0;
		if(new->hasenv == 1 && new->quote_type != 1)
			dollar_exec_with_quote(new, minishell); //세그폴트남

		split_argv_quotes_cmd(new);
	}
	//"asdf '$HOME' asdf"; "asdf'$HOME'asdf"
	else
	{

		if(new->hasenv == 1 && new->quote_type != 1)
			dollar_exec_with_quote(new, minishell); //세그폴트남
			ft_printf("커맨드가 쿼트가 아닐 경우'%d, %d'\n",new->hasenv, new->quote_type);
			split_argv(new);
			// if(new->hasenv == 1 && new->quote_type != 1)
			// 	dollar_exec_with_quote(new, minishell);
			// if(new->hasenv == 1 && new->quote_type == 2)
			// 	dollar_exec_with_quote(new, minishell);
		}

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