#include "../libft/libft.h"
#include "../minishell.h"

t_cmd *create_node(char *data)
{
     t_cmd *new;
     if (!(new = (t_cmd *)malloc(sizeof(t_cmd))))
         return (NULL);
     new->command = ft_strdup(data);
     new->next = NULL;
     return (new);
}

/*
void nb_of_cmds(t_minishell *minishell, char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ';')
			minishell->cmd_num++;
		i++;
	}
	minishell->cmd_num++;
}
*/

void get_input(t_minishell *minishell)
{
	char buf[2];
	char *input;
	

	//init
	minishell->cmd_num = 0;
	//

	buf[0] = ' ';
	buf[1] = '\0';
	input = ft_strdup("");
	while (buf[0] != '\n')
	{
		read(STDIN_FILENO, buf, 1);
		if (buf[0] != '\n')
			input = ft_strjoin(input, buf);
	}
	//nb_of_cmds(input);
	*minishell->cmd = *(t_cmd *)malloc(sizeof(t_cmd));
	t_cmd *curr = minishell->cmd;
	int start = 0;
	int end = 0;
	while (input[end])
	{
		start = end;
		while (input[end] && input[end] != ';')
			end++;
		printf("(%d %d)",start, end);

		if (input[end] == ';')
		{
			minishell->cmd->next = create_node(&input[end - start]);	
			minishell->cmd = minishell->cmd->next;
		}
		end++;
	}

    while (curr != NULL)               // 포인터가 NULL이 아닐 때 계속 반복
    {
        printf("%s\n", curr->command);    // 현재 노드의 데이터 출력
        curr = curr->next;
    }

//1. 한줄로 받아서 파싱을 하면 파싱을 하면서 연결리스트를 바로바로 만들수있다
//2. 하나하나씩 하면 연결리스트를 만들 필요가 없다 (이 경우 cd나 echo에서 2번째 인자만 따로 다뤄줘야됨)
//2번으로 결정!	 
	//할일 : parse_input에서 ; 별로 명령어 나누는 처리 해줘야함(linked list 사용해야할듯)
	//세미콜론 핸들링 함수


	//[해결] 할일 : 라인 끝자락에 공백이 들어갔을 경우 argc 추가하지않기.
/*	parse_input(minishell, input);
	//할일 : 이하 내용을 담을 함수 만들기, 함수는 ; 개수만큼 루프 돌도록
	if (!(ft_strncmp(minishell->cmd.command[0], "pwd", 3)))
	{
		if (minishell->cmd.argc == 1)
			printf("%s\n", getcwd(minishell->path, 4096));
		else
			printf("pwd: too many arguments\n");
	}
	//할일(나중에) : 명령어별로 함수 분할하기
	else if (!(ft_strncmp(minishell->cmd.command[0], "cd", 2)))
	{
		if (minishell->cmd.argc == 1)
			chdir("~"); //환경변수가 없어서 작동을 안합니다.
		else if (minishell->cmd.argc == 2)
		{
			if (chdir(minishell->cmd.command[1]) < 0) //경로가 실제 존재하는지 체크합니다.
				printf("cd: no such file or directory\n");
		}
		else if (minishell->cmd.argc > 2)
			printf("cd: too many arguments\n");
	}
	//할일 : free함수를 만들기.
	for (int i = 0; minishell->cmd.command[i]; i++)
		free(minishell->cmd.command[i]);*/
	//exit(1);
	/**input = ft_strnew(1);
	count = 1;
	i = 0;
	while ((ret = read(0, &buf, 1)) && buf != '\n')
	{
		*(*input + i++) = buf;
		*input = ft_realloc(*input, count, count + 1);
		count++;
	}
	*(*input + i) = '\0';
	if (!ret)
	{
		free(*input);
		ft_exit(input);
	}*/
	
}
