#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int		main(void)
{
	char *line = NULL;
	int fd = open("test", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_putendl(line);
		ft_memdel((void**)&line);
	}
	close(fd);
}
