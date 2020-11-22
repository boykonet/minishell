/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:53:52 by gkarina           #+#    #+#             */
/*   Updated: 2020/07/01 14:53:52 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			init_line(char **line, t_data *data)
{
	if ((data->var = ft_strchr(data->rem, '\n')))
	{
		data->count = 0;
		while (data->rem[data->count] != '\n')
			data->count++;
		if (((*line) = (char*)malloc(sizeof(char) * (data->count + 1))) == NULL)
			return (data->err = -1);
		ft_strlcpy(*line, data->rem, ++(data->count));
		(*line)[--(data->count)] = '\0';
		if ((data->temp = ft_strdup(&(data->rem[++(data->count)]))) == NULL)
		{
			free(*line);
			return (data->err = -1);
		}
		free(data->rem);
		data->rem = data->temp;
	}
	else
	{
		if ((*line = ft_strdup(data->rem)) == NULL)
			data->err = -1;
		free(data->rem);
		data->rem = NULL;
	}
	return (data->err);
}

static int			update_line(char **line, char *buff, t_data *data)
{
	buff[data->len] = '\0';
	if ((data->var = ft_strchr(buff, '\n')))
	{
		data->count = 0;
		while (buff[data->count] != '\n')
			data->count++;
		buff[data->count] = '\0';
		if ((data->rem = ft_strdup(&buff[++(data->count)])) == NULL)
			return (data->err = -1);
	}
	data->temp = *line;
	if ((*line = ft_strjoin(*line, buff)) == NULL)
	{
		free(data->rem);
		data->err = -1;
	}
	free(data->temp);
	return (data->err);
}

static int			prog_logic(char **line, int fd, t_data *data)
{
	char			buff[BUFFER_SIZE + 1];

	if (data->rem)
	{
		init_line(line, data);
		if (data->err == -1)
			return (-1);
	}
	else
	{
		if ((*line = ft_strdup("\0")) == NULL)
			data->err = -1;
	}
	while (!(data->var) && (data->len = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		if ((data->err = update_line(line, buff, data)) == -1)
			return (-1);
	}
	if (data->len == -1)
	{
		free(*line);
		free(data);
		return (-1);
	}
	return (0);
}

int					get_next_line(int fd, char **line)
{
	t_data			*data;
	static char		*rem;
	int				len;

	*line = NULL;
	if (BUFFER_SIZE < 0)
		return (-1);
	if ((data = (t_data*)malloc(sizeof(t_data))) == NULL)
		return (-1);
	data->rem = rem;
	data->len = 1;
	data->err = 0;
	data->var = NULL;
	if ((prog_logic(line, fd, data)) == -1)
		return (-1);
	rem = data->rem;
	len = data->len;
	free(data);
	return (len > 1 ? 1 : len);
}
