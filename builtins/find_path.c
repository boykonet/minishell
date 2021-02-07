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

static char			*read_dir(char **dirs, int i, char *old_cmd)
{
	struct dirent	*entry;
	char			*tmp;
	DIR				*name;
	char			*cmd;

	cmd = NULL;
	if (!(name = opendir(dirs[i])))
		return (NULL);
	while ((entry = readdir(name)))
	{
		if (!ft_strcmp(entry->d_name, old_cmd))
		{
			if (!(tmp = ft_strjoin(dirs[i], "/")))
				exit(errno);
			cmd = ft_strjoin(tmp, old_cmd);
			free(tmp);
			if (!cmd)
				exit(errno);
			break ;
		}
	}
	closedir(name);
	return (cmd);
}

char				*find_path(char *old_cmd, char *path)
{
	char			*cmd;
	char			**dirs;
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
		if ((cmd = read_dir(dirs, i, old_cmd)) != NULL)
			flag = 0;
		if (!flag)
			return (cmd);
		i++;
	}
	return (NULL);
}
