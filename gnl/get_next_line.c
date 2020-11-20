/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 08:10:29 by snaomi            #+#    #+#             */
/*   Updated: 2020/09/18 11:03:56 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		free_head(t_gnl **head, char **reminder)
{
	t_gnl		*tmp;

	if (*reminder)
	{
		free(*reminder);
		*reminder = NULL;
	}
	tmp = *head;
	if (*head)
		*head = (*head)->next;
	free(tmp);
}

static int		check_reminder(t_gnl *tmp, char **line)
{
	char		*ptr;
	char		*temp;

	if (tmp->reminder)
		if ((ptr = ft_strchr(tmp->reminder, '\n')))
		{
			*ptr = '\0';
			if (!(*line = ft_strdup(tmp->reminder)))
				return (-1);
			temp = tmp->reminder;
			if (!(tmp->reminder = ft_strdup(++ptr)))
				return (-1);
			free(temp);
		}
		else
		{
			if (!(*line = ft_strdup(tmp->reminder)))
				return (-1);
			free(tmp->reminder);
			tmp->reminder = NULL;
		}
	else if (!(*line = ft_strdup("")))
		return (-1);
	return (0);
}

static int			get_line(char **line, char *buf, t_gnl *tmp)
{
	char			*ptr;
	char			*temp;
	int				byte_read;

	if (check_reminder(tmp, line) == -1)
		return (-1);
	byte_read = 0;
	while (!(tmp->reminder) && (byte_read = read(tmp->fd, buf, 1)))
	{
		if (byte_read < 0)
			return (-1);
		buf[byte_read] = '\0';
		if ((ptr = ft_strchr(buf, '\n')))
		{
			*ptr = '\0';
			if (!(tmp->reminder = ft_strdup(++ptr)))
				return (-1);
		}
		temp = *line;
		if (!(*line = ft_strjoin(temp, buf)))
			return (-1);
		free(temp);
		temp = NULL;
	}
	return ((tmp->reminder || byte_read) ? 1 : 0);
}

int				get_next_line(int fd, char **line)
{
	static t_gnl	*head;
	char			*buf;
	int				gnl;

	if (fd < 0 || line == NULL || (!(buf = (char*)malloc((sizeof(char) * 2)))))
		return (-1);
	if (head == NULL)
		if (!(head = ft_lstnew_gnl(fd)))
			return (-1);
	if ((gnl = get_line(line, buf, head)) == 0)
		free_head(&head, &head->reminder);
	if (gnl == -1)
	{
		free_head(&head, &head->reminder);
		if (*line)
		{
			free(*line);
			*line = NULL;
		}
	}
	free(buf);
	return (gnl);
}
