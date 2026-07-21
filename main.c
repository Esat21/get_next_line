#include "get_next_line.h"
#include <fcntl.h>
#include <limits.h>

int main()
{
	int		fd;
	int		nb;
	char	*str;
	int 	i;

	fd = open("./trick.txt", O_RDONLY);
	// str = get_next_line(fd);
	// while (str)
	// {
	// 	printf("%s",  str);
	// 	free(str);
	// 	str = get_next_line(fd);
	// }
	// free(str);
	// read(fd, str, BUFFER_SIZE);
	// printf("%s",  str);
	// if (!str)
	// 	printf("hell");
	// free(str);
	i = 0;
	while (i < 10)
	{		
		str = get_next_line(fd);
		printf("%s",  str);
		free(str);
		i++;
	}
	close(fd);
}