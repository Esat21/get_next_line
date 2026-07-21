#include "get_next_line.h"
#include <fcntl.h>
#include <limits.h>

int main()
{
	int		fd;
	int		trick_fd;
	int		read_bytes;
	int		bytes_num;
	char	*str;
	char	*buff;

	fd = open("./trick.txt", O_RDONLY);
	str = malloc(1000);
	// while (str == get_next_line(fd))
	// {
	// 	printf("%s\n",  str);
	// 	free(str);
	// }
	str = get_next_line(fd);
	printf("%s",  str);
	close(fd);
}