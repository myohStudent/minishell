/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 10:33:16 by myoh              #+#    #+#             */
/*   Updated: 2020/12/23 10:34:03 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		ret = NULL;
	return (ret);
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
		temp = temp->next;
		i++;
	}
	free(temp);
	store[i] = NULL;
	return (store);
}