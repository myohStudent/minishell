#include "libft.h"
#include <stdio.h>

int				main(void)
{
	int				fd;
	char			*line;
	int				re;
	char			*str;
	str = ft_strnew(3);
	
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
