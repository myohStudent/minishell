/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 11:17:00 by myoh              #+#    #+#             */
/*   Updated: 2020/05/27 15:18:56 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			finding_n(char *stock)
{
	int				n;

	n = 0;
	while (stock[n] != '\0')
	{
		if (stock[n] == '\n')
			return (n);
		n++;
	}
	return (-1);
}

static int			line_coupe(char **stock, char **line, int n)
{
	int				l;
	char			*imsi;

	(*stock)[n] = '\0';
	*line = ft_strdup(*stock);
	l = ft_strlen(*stock + n + 1);
	if (l == 0)
	{
		free(*stock);
		*stock = 0;
		return (1);
	}
	imsi = ft_strdup(*stock + n + 1);
	free(*stock);
	*stock = imsi;
	return (1);
}

static int			get_output(char **stock, char **line, int size)
{
	int				n;

	if (size < 0)
		return (-1);
	if (*stock && (n = finding_n(*stock)) >= 0)
		return (line_coupe(stock, line, n));
	else if (*stock)
	{
		*line = *stock;
		*stock = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int					get_next_line(int fd, char **line)
{
	int				n;
	int				size;
	static char		*stock[255];
	char			buf[BUFFER_SIZE + 1];

	if (fd < 0 || fd <= read(fd, 0, 0)|| line == 0 || BUFFER_SIZE <= 0)
		return (-1);
	while ((size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[size] = '\0';
		stock[fd] = j_strjoin(stock[fd], buf);
		n = finding_n(stock[fd]);
		if (n >= 0)
			return (line_coupe(&stock[fd], line, n));
	}
	return (get_output(&stock[fd], line, size));
}