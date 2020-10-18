#include "../minishell.h"

int			    ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
} 

void    		cpy_env(t_minishell *minishell, int j)
{
	int         i;
	int         c;

	i = 0;
	c = 0;
	minishell->export_set = (char **)ft_memalloc(sizeof(char *) * (j + 1));
	while (minishell->env_set[i] != NULL)
	{
		minishell->export_set[i] = ft_strdup(minishell->env_set[i]);
		i++;
		ft_printf("%d ", i);
		ft_printf("\n");
	}
	//ft_printf("cpy_env 나옴\n");
}

static void     sort_export(t_minishell *minishell, int j)
{
	int i;
	int c;
	char *temp;
	int k;

	c = 0;
	ft_printf("j : %d\n", j);
	ft_printf("---sort중---\n");
	/*
		{ 
   		
   		for (i = 0; i < n-1; i++)       
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
			  */
	
	i = 0;
	while (i < j - 1 && minishell->export_set[i])
	{
		k = 0;
		while (k < j - i - 1 && minishell->export_set[k + 1])
		{
			if (ft_strcmp(minishell->export_set[k], minishell->export_set[k + 1]) > 0)
			{
				ft_printf("%d ", k);
				temp = minishell->export_set[k];
				minishell->export_set[k] = minishell->export_set[k + 1];
				//free(minishell->export_set[k + 1]);
				minishell->export_set[k + 1] = temp;
			}
			k++;
		}
		i++;
	}
	while (minishell->export_set[i])
		i++;
	minishell->env_currnb = i;
	ft_printf("현재 currnb 개수: (%d) ", minishell->env_currnb);
	ft_printf("---sort끝남---\n");
}

char	**arr_realloc(t_minishell *minishell, char *line)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (arr_len(minishell->export_set) + 2));
	while (minishell->export_set[i] != NULL)
	{
		res[i] = ft_strdup(minishell->export_set[i]);
		i++;
	}
	ft_printf("(%d)",i);
	res[i] = ft_strdup(line);
	res[i + 1] = NULL;
	ft_printf("(%d)\n", i);
	free_arr(minishell->export_set);
	minishell->env_currnb = i + 1; // 넘버 추가
	return (res);
}

int             cmd_export(t_cmd *curr, t_minishell *minishell)
{
	int j;
	int i;
	int unseenfl;
	char    **str;

	i = 0;
	unseenfl = 0;
	j = 0;
	//cpy_env(minishell, minishell->env_nb);
	ft_printf("----요기---\n");

	if (curr->argc == 1)
	{
		sort_export(minishell, minishell->env_nb);
		ft_printf("현재 export 갯수 : %d\n",arr_len(minishell->export_set));
		i = 0;
		while (minishell->export_set[i] && i < arr_len(minishell->export_set))
		{
			ft_printf("declare -x %d ", i);
			ft_printf("%s\n", minishell->export_set[i]);
			i++;
		}
		ft_printf("\n");
		return (1);
	}

	if (curr->argc == 2 && curr->option != NULL)
	{
		if ((ft_strchr(curr->option,'=') != 0)) // 예외처리
		{
			ft_printf("----if 진입--\n");
			while (curr->option[j] && curr->option[j] != '=')
				j++;
			ft_printf("(%d, %d, %d)\n",j, i, unseenfl);
			while (minishell->export_set[i] != NULL && i < minishell->env_currnb)
			{
				ft_printf("%s\n",minishell->export_set[i]);
				if (ft_strncmp(minishell->export_set[i], curr->option, j + 1) == 0)
				{
					ft_printf("----if 진입--\n");
					minishell->export_set[i] = ft_strdup(curr->option);
					unseenfl = 1;
					break ;
				}
				i++;
				ft_printf("(%d)",i);
			}
		ft_printf("----uneenfl=0 바로 전---\n");
			if (unseenfl == 0)
			{
				ft_printf("(%d)\n",j);
				if (!(minishell->export_set = arr_realloc(minishell, curr->option)))
					return (0);
			}
		}
	}	
	return (1);
}