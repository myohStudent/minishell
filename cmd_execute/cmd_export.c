#include "../minishell.h"

int cmd_export(t_cmd *curr, t_minishell *minishell)
{
	if(!minishell->export_list)
	{
		copy_env();
		sort_env(); //init_nb까지 버블소팅
	}
	if (curr->argc == 0)
		print_env();
	if (curr->argc == 1)
		env_export에 curr->option 넣기(파싱)
	if (curr->argv > 1)
		split=로 잘라서 curr, curr->option 넣기(파싱)
}