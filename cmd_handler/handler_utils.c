/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:50:45 by myoh              #+#    #+#             */
/*   Updated: 2020/11/15 16:11:03 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

int		arr_len(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

char	*parse_space(char *s, char *space)
{
	int	i;

	i = 0;
	if (!space || !s)
		return (NULL);
	while (ft_strchr(s, space && s[i] != '\0'))
	{
		s++;
		i++;
	}
	i = ft_strlen(s);
	while (ft_strchr(space, s[i]) && s != 0)
		i--;
	return (ft_substr(s, 0, i + 1));
}