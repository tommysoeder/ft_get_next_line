#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stddef.h>
#include "../get_next_line.h"

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("lotr.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while ((line = get_next_line(fd)))
	{	
		printf("%s\n", line);
		free(line);
	}
	close(fd);
}