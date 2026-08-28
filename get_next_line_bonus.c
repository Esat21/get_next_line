/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esyaman <esyaman@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 23:35:06 by esyaman           #+#    #+#             */
/*   Updated: 2026/08/28 16:17:25 by esyaman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_and_cut(char *result, char *buff, int index)
{
	char	*joined;
	int		l_result;

	l_result = ft_strlen(result);
	joined = malloc(l_result + index + 2);
	if (!*buff || !joined)
		return (NULL);
	ft_strlcpy(joined, result, l_result + 1);
	ft_strlcpy(joined + l_result, buff, index + 2);
	ft_strlcpy(buff, buff + index + 1, BUFFER_SIZE);
	free(result);
	return (joined);
}

static char	*joiner(char *result, char *buff)
{
	int		l_result;
	int		l_buff;
	char	*joined;

	joined = NULL;
	l_result = ft_strlen(result);
	l_buff = ft_strlen(buff);
	if ((l_result + l_buff) > 0)
	{
		joined = malloc((l_result + l_buff + 1));
		if (!joined)
			return (NULL);
		if (joined)
			ft_strlcpy(joined, result, l_result + 1);
		if (buff)
			ft_strlcpy(joined + l_result, buff, l_buff + 1);
	}
	free(result);
	free(buff);
	return (joined);
}

static char	*read_and_terminate(int fd)
{
	char	*buffer;
	int		i;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	i = -1;
	while (++i < BUFFER_SIZE + 1)
		buffer[i] = 0;
	if (read(fd, buffer, BUFFER_SIZE) <= 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buff[1024] = {};
	char		*result;
	int			i;

	result = NULL;
	if (!buff[fd])
		buff[fd] = read_and_terminate(fd);
	i = -1;
	while (++i >= 0 && buff[fd])
	{
		if (!buff[fd][i])
		{
			result = joiner(result, buff[fd]);
			buff[fd] = read_and_terminate(fd);
			i = 0;
		}
		if (buff[fd] && buff[fd][i] == '\n')
		{
			result = extract_and_cut(result, buff[fd], i);
			i = 0;
			break ;
		}
	}
	return (result);
}

// #include "get_next_line.h"
// #include <fcntl.h>
// #include <limits.h>

// int main()
// {
// 	int		fd1, fd2, fd3;
// 	char	*str1, *str2, *str3;

// 	fd1 = open("./test1", O_RDONLY);
// 	fd2 = open("./test2", O_RDONLY);
// 	fd3 = open("./test3", O_RDONLY);
// 	str1 = get_next_line(fd1); 
// 	str2 = get_next_line(fd2);
// 	str3 = get_next_line(fd3);
// 	while (str1 || str2 || str3)
// 	{
// 		if (str1)
// 			printf("fd1: %s",  str1);
// 		if (str2)
// 			printf("fd2: %s",  str2);
// 		if (str3)
// 			printf("fd3: %s",  str3);
// 		free(str1);
// 		free(str2);
// 		free(str3);
// 		str1 = get_next_line(fd1); 
// 		str2 = get_next_line(fd2);
// 		str3 = get_next_line(fd3);
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (3547);
// }