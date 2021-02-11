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

static int 			err_path(char *old_cmd)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(old_cmd, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (127);
}

char				*find_path(char *old_cmd, char *path, int *status)
{
	char			*cmd;
	char			**dirs;
	int				i;

	i = 0;
	dirs = NULL;
	cmd = NULL;
	if (path)
	{
		if (!(dirs = ft_split(path, ':')))
			exit(errno);
	}
	else
		*status = err_path(old_cmd);
	while (path && dirs[i])
	{
		if ((cmd = read_dir(dirs, i, old_cmd)))
			break ;
		i++;
	}
	free_string(dirs);
	if (cmd)
		return (cmd);
	return (NULL);
}
