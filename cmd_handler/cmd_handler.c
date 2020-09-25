#include "../libft/libft.h"
#include "../minishell.h"

void cmd_handler(t_minishell *minishell)
{
	char buf[2];
	char *input;
	t_cmd *curr;

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
	
	//1. 한줄로 받아서 파싱을 하면 파싱을 하면서 연결리스트를 바로바로 만들수있다
	//2. 하나하나씩 하면 연결리스트를 만들 필요가 없다 (이 경우 cd나 echo에서 2번째 인자만 따로 다뤄줘야됨)
	//2번으로 결정!	
	//[해결] 할일 : 이하 내용을 parse 함수에 담기
	//[해결] 할일 : parse_input에서 ; 별로 명령어 나누는 처리 해줘야함(linked list 사용해야할듯)
	//[해결] 할일 : 라인 끝자락에 공백이 들어갔을 경우 argc 추가하지않기.

	minishell->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	curr = minishell->cmd;
	parse_cmd(minishell->cmd, input);

	//할일 : 이하 내용을 담을 함수 만들기 (명령어 처리기)

	int i = 0;
    while (curr != NULL)               // 포인터가 NULL이 아닐 때 계속 반복
    {
        printf("%d : %s|\n", i, curr->command);    // 현재 노드의 데이터 출력
		i++;
		//할일 : 명령어별로 함수 분할하기. 함수마다 노드가 비어있는 경우 return -1 처리하기.
		if (curr->command) {
			if (!(ft_strncmp(curr->command, "pwd", 3)))
			{
				if (curr->argc == 1)
					printf("%s\n", getcwd(minishell->path, 4096));
				else
					printf("pwd: too many arguments\n");
			}
			else if (!(ft_strncmp(curr->command, "cd", 2)))
			{
				if (curr->argc == 1)
					chdir("~"); //환경변수가 없어서 작동을 안합니다.
				else if (curr->argc == 2)
				{
					if (chdir(curr->option) < 0) //경로가 실제 존재하는지 체크합니다.
						printf("cd: no such file or directory\n");
				}
				else if (curr->argc > 2)
					printf("cd: too many arguments\n");
			}
		}
        curr = curr->next;
    }
	//free 함수
	t_cmd *next;

	curr = minishell->cmd;
	while (curr != NULL)
	{
		next = curr->next;
		curr->command = 0;		
		free(curr);
		curr = curr->next;
	}
/*
	//할일 : free함수를 만들기.
	for (int i = 0; minishell->cmd.command[i]; i++)
		free(minishell->cmd.command[i]);*/
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
