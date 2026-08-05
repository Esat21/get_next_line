/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esyaman <esyaman@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 23:35:06 by esyaman           #+#    #+#             */
/*   Updated: 2026/08/05 18:26:32 by esyaman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char		*buff = NULL;
	int				bytes_read;

	if (!buff)
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		buff[0] = '\0';
	}
	result = NULL;
	while (find_new_line(buff, '\n') < 0)
	{
		if (buff[0] != '\0')
			result = result_append(result, buff, BUFFER_SIZE);
		bytes_read = read_and_terminate(fd, buff);
		if (bytes_read <= 0)
			break ;
	}
	if (find_new_line(buff, '\n') >= 0)
		result = extract_line(buff, result);
	if (bytes_read <= 0 && buff)
		free(buff);
	return (result);
}

#include "get_next_line.h"
#include <fcntl.h>
#include <limits.h>

int main()
{
	int		fd;
	char	*str;

	fd = open("./test.txt", O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		printf("%s",  str);
		free(str);
	}
	close(fd);
}