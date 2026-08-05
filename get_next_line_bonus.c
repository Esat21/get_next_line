/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esyaman <esyaman@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 23:35:06 by esyaman           #+#    #+#             */
/*   Updated: 2026/08/05 18:11:13 by esyaman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*result_append(char *result, char *buff, int pos)
{
	char	*temp;

	temp = malloc(ft_strlen(result) + pos + 1);
	if (!temp)
		return (NULL);
	if (result)
	{
		ft_strlcpy(temp, result, ft_strlen(result) + 1);
		ft_strlcat(temp, buff, ft_strlen(temp) + pos + 1);
	}
	else
		ft_strlcpy(temp, buff, pos + 1);
	free(result);
	return (temp);
}

static int	read_and_terminate(int fd, char *buff)
{
	int	bytes_read;

	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (bytes_read > 0)
		buff[bytes_read] = '\0';
	else
		buff[0] = '\0';
	return (bytes_read);
}

static char	*extract_line(char *buff, char *result)
{
	int	pos;

	pos = find_new_line(buff, '\n');
	result = result_append(result, buff, pos);
	ft_strlcpy(buff, (buff + pos), ft_strlen(buff));
	return (result);
}

char	*get_next_line(int fd)
{
	char			*result;
	static char		*buff[1024] = {};
	int				bytes_read;

	if (!buff[fd])
	{
		buff[fd] = malloc(BUFFER_SIZE + 1);
		if (!buff[fd])
			return (NULL);
		buff[fd][0] = '\0';
	}
	result = NULL;
	while (find_new_line(buff[fd], '\n') < 0)
	{
		if (buff[fd][0] != '\0')
			result = result_append(result, buff[fd], BUFFER_SIZE);
		bytes_read = read_and_terminate(fd, buff[fd]);
		if (bytes_read <= 0)
			break ;
	}
	if (find_new_line(buff[fd], '\n') >= 0)
		result = extract_line(buff[fd], result);
	if (bytes_read <= 0)
		free(buff);
	return (result);
}

// #include "get_next_line.h"
// #include <fcntl.h>
// #include <limits.h>

// int main()
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("./test", O_RDONLY);
// 	while ((str = get_next_line(fd)))
// 	{
// 		printf("%s",  str);
// 		free(str);
// 	}
// 	close(fd);
// }