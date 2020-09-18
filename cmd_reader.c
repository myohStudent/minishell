/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 12:26:13 by myoh              #+#    #+#             */
/*   Updated: 2020/09/18 16:25:17 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./libft/libft.h"
#include "./minishell.h"

int		cmd_reader(int fd, char **line)
{
	int		i;
	char	*buf;
	char	*new_l;

	i = 0;
	if (get_next_line(fd, line) == 0)
	
}