/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:30:25 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/07 16:00:10 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "other.h"
#include "minishell.h"

static int		chdir_in_work(char *path)
{
	if ((chdir(path) < 0))
	{
		ft_putstr_fd("-minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

static int		get_pwd(char **pwd)
{
	errno = 0;
	ft_pwd(pwd);
	if (errno > 0)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
	return (0);
}

static int		free_pwd_res(char *res, char *pwd, int status)
{
	free(res);
	free(pwd);
	return (status);
}

int				ft_cd(t_list *args, t_env **env)
{
	char		*res;
	char		*pwd;
	int			status;

	status = 0;
	pwd = NULL;
	res = find_data_in_env(*env, "HOME", 0);
	if (!args && res && !ft_strcmp(res, ""))
		return (status);
	res = NULL;
	if ((status = arg_for_cd(args, env, &res)) > 0)
		return (free_pwd_res(res, pwd, status));
	if ((status = chdir_in_work(res)) > 0)
		return (free_pwd_res(res, pwd, status));
	if (get_pwd(&pwd) > 0)
		return (free_pwd_res(res, pwd, status));
	change_pwd(env, pwd);
	if (args && !ft_strncmp(args->content, "-", ft_strlen(args->content)))
		ft_putendl_fd(res, 1);
	free(res);
	free(pwd);
	return (status);
}
