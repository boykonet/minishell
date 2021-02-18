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
#include "utils.h"

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

static void			is_dir(char *cmd, int *status)
{
	struct stat		s;

	if (!ft_strchr(cmd, '/') && check_command(cmd))
	{
		ft_putstr_fd("-minishell ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		*status = 127;
	}
	else if (!(stat(cmd, &s)))
	{
		if (s.st_mode & S_IFDIR)
		{
			ft_putstr_fd("-minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": is a directory", 2);
			*status = 126;
		}
	}
}

static void			fn_arg_req(char *cmd, int *status)
{
	if (!ft_strcmp(cmd, "."))
	{
		ft_putendl_fd("-minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		*status = 2;
	}
}

static char			**ret_dirs(char *old_cmd, char *path, int *status)
{
	char			**dirs;

	dirs = NULL;
	if (path)
	{
		if (!(dirs = ft_split(path, ':')))
			exit(errno);
	}
	else
	{
		ft_putstr_fd("-minishell: ", 2);
		ft_putstr_fd(old_cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		*status = 127;
	}
	return (dirs);
}

char				*find_path(char *old_cmd, char *path, int *status)
{
	char			*cmd;
	char			**dirs;
	int				i;

	i = 0;
	cmd = NULL;
	dirs = ret_dirs(old_cmd, path, status);
	if (*status > 0)
		return (NULL);
	fn_arg_req(old_cmd, status);
	while (!(*status) && dirs[i] && ft_strcmp(old_cmd, "..") && \
	!ft_strchr(old_cmd, '/') && check_command(old_cmd))
	{
		if ((cmd = read_dir(dirs, i, old_cmd)))
			break ;
		i++;
	}
	free_string(dirs);
	if (cmd)
		return (cmd);
	if (!(*status))
		is_dir(old_cmd, status);
	return (NULL);
}
