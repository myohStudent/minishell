/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:55:01 by myoh              #+#    #+#             */
/*   Updated: 2020/11/01 15:37:13 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*void	ft_exit(void)
{
	write(1, "\n", 1);
	exit(1);
}*/

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

t_env		*new_env(char **str)
{
	t_env	*new;

	if (!(new = ft_memalloc(sizeof(t_env))))
		return (new); // ?????? t_env???? 반환 어쩔? 
	new->variable = ft_strdup(str[0]);
	// env value값이 있을 때와 없을 때가 있어서 예외 처리를 해야 한다
	if (str[1] != NULL)
		new->value = ft_strdup(str[1]);
	else
		new->value = ft_strdup("");
	return (new);
}

char		**set_env(t_minishell *minishell)
{
	t_list	*temp;
	int		i;
	char	**env;
	char	*imsi1;
	char	*imsi2;

	i = 0;
	if (minishell->env_set)
		free_arr(minishell->env_set);
	if (!(env = ft_calloc(1, sizeof(char *) *
					(ft_lstsize(minishell->env_list) + 1))))
		return (NULL);
	temp = minishell->env_list;
	while (temp)
	{	
		//ft_strjoin으로 variable과 =를 한 줄로 입력
		imsi1 = ft_strjoin(((t_env *)(temp->content))->variable, "=");
		ft_printf("%s", imsi1);
		//그 줄에다 다시 뒷부분 입력
		imsi2 = ((t_env *)(temp->content))->value;
		ft_printf("%s \n", imsi2);
		env[i] = ft_strjoin(imsi1, imsi2);
		free(imsi1);
		free(imsi2);
		i++; //
		temp = temp->next; //다음 줄로 가시오!
	}
	env[i] = NULL;
	return (env);
}

void		init_env(char **env, t_minishell *minishell)
{
	t_list	*templst;
	t_env	*temp; 
	int		i;
	char	**str;
	
	i = 0;
	temp = (t_env *)malloc(sizeof(t_env)); //초기화 필요 없을 것 같지만?
	temp->variable = NULL;
	temp->value = NULL;
//	temp->index = 0;
	while (env[i])
	{
		str = ft_split(env[i], '='); // split해서 나눠 놓기
		if (!(temp = new_env(str))) // 나눈 문자열을 따로 따로 temp 임시 구조체에 넣기
		{
			free_arr(str);
			return ;
		}
		//templst = ft_lstnew(temp); // 템프lst에 저장
		//ft_lstadd_back(&minishell->env_list, templst); // env_list포인터에다 templst저장
		ft_lstadd_back(&minishell->env_list, ft_lstnew(temp));
		free_arr(str);
		i++;
	}
	// 다 넣은 뒤에 다시 하나의 이중배열에 입력함... -> 이거 넣고 env 명령어 치면 에러 발생.
	//minishell->env_set = set_env(minishell);
	minishell->export_set = NULL; 
}

int		ft_before_chr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	return (0);	
}



int	arr_len(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

/*
char	**set_env(char **env)
{
	int		i;
	int		j;
	char	**new;
	char	*temp;

	i = arr_len(env);
	if (!(new = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		exit(1);
	new[0] = NULL;
	i = 0;
	while (env[i])
	{
		if (!(new[i] = ft_strdup(env[i])))
			exit(1);
		i++;
	}
	return (new);
}

void init_env(char **env, t_minishell *minishell)
{
	int i;

	i = 0;
	minishell->env_set = set_env(env);
	minishell->env_nb = arr_len(minishell->env_set);
	minishell->env_currnb = minishell->env_nb;
	cpy_env(minishell, minishell->env_nb);
}

int		count_mots(char *str)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (ISSPACE(str[i]))
			i++;
		if (!ISSPACE(str[i]) && str[i] != '\0')
			count++;
		while (!ISSPACE(str[i]) && str[i] != '\0')
			i++;
	}
	return (count);
}*/