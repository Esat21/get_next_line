/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esyaman <esyaman@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 23:35:06 by esyaman           #+#    #+#             */
/*   Updated: 2026/07/21 11:34:55 by esyaman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *result_append(char *result, char *buff, int pos)
{
	char	*temp;

	temp = malloc(ft_strlen(result) + pos + 1);
	ft_strlcpy(temp, result, ft_strlen(result) + 1);
	ft_strlcat(temp, buff, ft_strlen(temp) + pos + 1);
	free(result);
	result = malloc(ft_strlen(temp) + 1);
	ft_strlcpy(result, temp, ft_strlen(temp));
	free(temp);
	return (result);
}

char	*get_next_line(int fd)
{
	char			*result;
	static char		*hold = NULL;
	char			*buff;

	buff = malloc(BUFFER_SIZE + 1);
	if (!hold)
		read(fd, buff, BUFFER_SIZE);
	else
		ft_strlcpy(buff, hold, ft_strlen(hold) + 1);
	if (ft_strchr_n(buff, '\n') >= 0)
	{
		result = malloc(ft_strchr_n(buff, '\n') + 1);
		ft_strlcpy(result, buff, ft_strchr_n(buff, '\n'));
		return (result);
	}
	else
	{
		result = malloc(BUFFER_SIZE + 1);
		ft_strlcpy(result, buff, BUFFER_SIZE + 2);
		read(fd, buff, BUFFER_SIZE);
		while (ft_strchr_n(buff, '\n') < 0)
		{
			result_append(result, buff, BUFFER_SIZE + 1);
			read(fd, buff, BUFFER_SIZE);
		}
		if (ft_strchr_n(buff, '\n') >= 0 || !buff)
		{
			result_append(result, buff, ft_strchr_n(buff, '\n') + 1);
			hold = malloc(ft_strlen(buff + ft_strchr_n(buff, '\n')) + 2);
			ft_strlcpy(hold, (buff + ft_strchr_n(buff, '\n')), (ft_strlen(buff) - ft_strchr_n(buff, '\n')));
		}
	}
	return (result);
}
