/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 23:38:15 by myoh              #+#    #+#             */
/*   Updated: 2020/12/14 20:40:52 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		add_node(t_cmd *target, char *s)
{
	t_cmd *new = (t_cmd *)malloc(sizeof(t_cmd));  
    new->next = target->next;
    new->command = ft_strdup(s);
    target->next = new;
}

t_cmd		*reverse_node(t_cmd *head)
{
    t_cmd *p;
	t_cmd *q;
	t_cmd *r;

    p = head->next;
	q = NULL;
	r = NULL;
    //q = (t_cmd *)malloc(sizeof(t_cmd));
    while (p != NULL)
	{
        r = q;
        q = p;
        p = p->next;
        q->next = r;
		head->next = q;
    }
    return (q);
}

void	delete_space_flag(char **temp, char flag)
{
	int		i;

	i = 0;
	if (*temp)
	{
		while ((*temp)[i] == ' ')
			i++;
		(*temp) = ft_strdup((*temp) + i);
		if ((*temp)[i] == flag)
			i++;
		(*temp) = ft_strdup((*temp) + i);
		while ((*temp)[i] == ' ')
			i++;
		(*temp) = ft_strdup((*temp) + i);
	}
}

void	flag_checker(char flag)
{
	if (flag)
	{
		if (flag == '>')
			flags[1] = 1;
		else if (flag == '|')
			flags[0] = 1;
		else if (flag == '<')
			flags[2] = 1;
		else if (flag == 3) // >>
			flags[3] = 1; 
	}
}

int		parse_flag(t_cmd *curr, t_cmd *head,
				t_minishell *minishell, char flag)
{
	int		i;
	int		j;
	char		*temp;
	char		*temp2;
	char		*temp3;
	t_cmd	*next;

	flag_checker(flag);
	i = 0;
	temp = ft_strjoin(curr->command, " ");
	temp = ft_strjoin(temp, curr->option);
	ft_printf("%s\n", temp);
	curr = curr->next;
	head->next = NULL;

	if (temp != NULL)
	{
		delete_space_flag(&temp, flag);
		i = 0;
		if (temp != NULL)
		{
			while (temp[i])
			{ 
				while (temp[i] == flag && temp[i + 1] != '\0')
				{
					temp2 = ft_substr(temp, 0, i);
					//option 넣는 거랑 다른 부호 파싱이 여기 들어가야 함.
					add_node(head, space_trim(temp2));
					free(temp2);
					free(temp);
					temp = ft_substr(temp, i + 1, ft_strlen(temp) - i);
					temp2 = NULL;
					i = -1;
				}
				i++;
			}
			if (temp) // 마지막 cmd
			{
				add_node(head, space_trim(temp));
				temp = NULL;
				free(temp);
			}
			free(temp2);				
		}
	}
	return (1);
}

char	**store_commands(t_cmd *scmd, t_minishell *minishell)
{
	char	**store;
	t_cmd	*temp;
	int		i;

	i = 1;
	if (!scmd->command)
		return (NULL);
	if (!(store = (char **)ft_calloc(1, sizeof(char *) * (minishell->cnt + 2))))
		return (NULL);
	store[0] = ft_strdup(scmd->command);
	temp = scmd;
	while (temp)
	{
		store[i] = ft_strdup(temp->command);
		//ft_printf("store[%d]: /%s/\n", i, store[i]);
		temp = temp->next;
		i++;
	}
	free(temp);
	store[i] = NULL;
	return (store);
}

void get_path(t_env *list, t_minishell *minishell)
{
	char	**bin;
	char *temp;
	int i;
	t_env *l;

	l = list;
	i = 0;
	temp = NULL;
	while (l && i < minishell->env_currnb)
	{
		if (ft_strcmp(l->variable, "PATH") == 0)
		{
			temp = ft_strdup(l->value);
			break ;
		}
		l = l->next;
		i++;
	}
	if (temp)
	{
		bin = ft_split(temp, ':');
		free(temp);
	}
	i = 0;
	while (bin[i])
		i++;
	pipe_bin = NULL;
	pipe_bin = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (bin && bin[i])
	{
		pipe_bin[i] = ft_strjoin(bin[i], "/");
		free(bin[i]);
		i++;
	}
}

char	*open_directory(char *path, char *command)
{
	DIR				*dir;
	struct dirent	*dent;

	dir = opendir(path);
	if (dir)
	{
		while ((dent = readdir(dir)))
		{
			if (ft_compare(dent->d_name, command))
			{
				if (dir)
					closedir(dir);
				return (ft_strjoin(path, command));
			}
		}
	}
	if (dir)
		closedir(dir);
	return (NULL);
}

char	*get_bin(t_minishell *minishell, char *command)
{
	char	*ret;
	int		i;

	if (!command)
		return (NULL);
	if (is_char_here('/', command) >= 0)
		return (ft_strdup(command));
	if (!pipe_bin)
	 	return (ft_strjoin("/bin/", command));
	i = 0;
	while (pipe_bin &&pipe_bin[i])
	{
		ret = open_directory(pipe_bin[i], command);
		if (ret)
			return (ret);
		i++;
	}
	if (ret == NULL)
		ret = ft_strjoin("/bin/", command);
	return (ret);
}