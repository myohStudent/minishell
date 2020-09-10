/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:59:22 by myoh              #+#    #+#             */
/*   Updated: 2020/05/27 15:17:47 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

int				main(void)
{
	int				fd;
	char			*line;
	int				re;

	fd = open("text.txt", O_RDONLY);
	while ((re = get_next_line(fd, &line)))
	{
		printf("%d|%s\n", re, line);
		free(line);
		line = NULL;
	}
	printf("%d|%s\n", re, line);
	free(line);
	line = NULL;
	return (0);
}
