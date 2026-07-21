/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esyaman <esyaman@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 23:35:06 by esyaman           #+#    #+#             */
/*   Updated: 2026/07/21 16:55:29 by esyaman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*result_append(char *result, char *buff, int pos)
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

char	*get_next_line(int fd)
{
	char			*result;
	static char		*buff = NULL;
	int				b_r;

	result = NULL;
	if(!buff)
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (NULL);
		b_r = read(fd, buff, BUFFER_SIZE);
		if (b_r <= 0)
			return (NULL);
		buff[BUFFER_SIZE] = '\0';
	}
	while (ft_strchr_n(buff, '\n') < 0 && b_r > 0)
	{
		result = result_append(result, buff, BUFFER_SIZE + 1);
		b_r = read(fd, buff, BUFFER_SIZE);
		buff[BUFFER_SIZE] = '\0';
	}
	if (ft_strchr_n(buff, '\n') >= 0)
	{
		result = result_append(result, buff, ft_strchr_n(buff, '\n'));
		ft_strlcpy(buff, (buff + ft_strchr_n(buff, '\n')), ft_strlen(buff));
	}
	return (result);
}
