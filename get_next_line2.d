
char *result_append(char *result, char *buff, int pos)
{
	char	*temp;

	temp = malloc(ft_strlen(result) + pos + 1);
	ft_strlcpy(temp, result, ft_strlen(result) + 1);
	ft_strlcat(temp, buff, ft_strlen(temp) + pos);
	free(result);
	result = malloc(ft_strlen(temp) + 1);
	ft_strlcpy(result, temp, ft_strlen(temp) + 1);
	free(temp);
	return (result);
}

char	*get_next_line(int fd)
{
	char			*result;
	static char		*hold = NULL;
	char			*buff;

	// todo remove
	buff = calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!hold)
		read(fd, buff, BUFFER_SIZE);
	else
	{
		ft_strlcpy(buff, hold, ft_strlen(hold));
		// printf("Hold: %s\n", hold);
	}	
	if (ft_strchr_n(buff, '\n') >= 0)
	{
		result = calloc(ft_strchr_n(buff, '\n') + 1, sizeof(char)); // todo switch to malloc
		ft_strlcpy(result, buff, ft_strchr_n(buff, '\n') + 1);
		return (result);
	}
	else
	{
		result = malloc(BUFFER_SIZE + 1);
		ft_strlcpy(result, buff, BUFFER_SIZE + 1);
		read(fd, buff, BUFFER_SIZE);
		while (ft_strchr_n(buff, '\n') < 0)
		{
			result_append(result, buff, BUFFER_SIZE);
			read(fd, buff, BUFFER_SIZE);
		}
		if (ft_strchr_n(buff, '\n') >= 0)
		{
			printf("Buff:%s\n", buff);
			result_append(result, buff, ft_strchr_n(buff, '\n'));
			hold = malloc(ft_strlen(buff + ft_strchr_n(buff, '\n')) + 2);
			ft_strlcpy(hold, (buff + ft_strchr_n(buff, '\n')), ft_strlen(buff));
			// printf("remaining buff:%s\n", hold);
		}
	}
	return (result);
}