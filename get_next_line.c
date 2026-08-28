/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esyaman <esyaman@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 23:35:06 by esyaman           #+#    #+#             */
/*   Updated: 2026/08/28 16:20:58 by esyaman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*buff = NULL;
	char		*result;
	int			i;

	result = NULL;
	if (!buff)
		buff = read_and_terminate(fd);
	i = -1;
	while (++i >= 0 && buff)
	{
		if (!buff[i])
		{
			result = joiner(result, buff);
			buff = read_and_terminate(fd);
			i = 0;
		}
		if (buff && buff[i] == '\n')
		{
			result = extract_and_cut(result, buff, i);
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
// 	int		fd;
// 	char	*str;

// 	fd = open("examples", O_RDONLY);
// 	while ((str = get_next_line(fd)))
// 	{
// 		printf("%s",  str);
// 		free(str);
// 	}
// 	close(fd);
// }