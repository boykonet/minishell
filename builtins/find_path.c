/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:49:13 by snaomi            #+#    #+#             */
/*   Updated: 2021/01/23 17:55:53 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"

char				*find_path(char *old_cmd, char *path)
{
	char			*tmp;
	char 			*cmd;
	char			**dirs;
	DIR				*name;
	struct dirent	*entry;
	int				i;
	int				flag;

	i = 0;
	flag = 1;
	dirs = NULL;
	if (path)
		if (!(dirs = ft_split(path, ':')))
			exit(errno);
	while (path && dirs[i])
	{
		cmd = NULL;
		if (!(name = opendir(dirs[i])))
			return (NULL);
// The readdir() function returns a pointer
// to a dirent structure, or NULL if an error occurs or end of the directory stream is reached. 
// On error, errno is set appropriately. 
		while ((entry = readdir(name)))
		{
// d_name - Это поле содержит имя файла с завершающим null.
			if (!ft_strcmp(entry->d_name, old_cmd))
			{				
				if (!(tmp = ft_strjoin(dirs[i], "/")))
					exit(errno);
				cmd = ft_strjoin(tmp, old_cmd);
				free(tmp);
				if (!cmd)
					exit(errno);
				flag = 0;
				break ;
			}
		}
		closedir(name);
		if (!flag)
			return (cmd);
		i++;
	}
	return (NULL);
}