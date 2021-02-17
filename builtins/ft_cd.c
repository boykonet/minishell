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

static void 	pwd_oldpwd(t_env **env, t_env **pwd, t_env **oldpwd)
{
	if (!(*pwd))
	{
		add_params_env(env, "PWD", "");
		(*pwd) = find_list_env(*env, "PWD", 0);
	}
	if (!(*oldpwd))
	{
		add_params_env(env, "OLDPWD", "");
		(*oldpwd) = find_list_env(*env, "OLDPWD", 0);
	}
}

static void		change_pwd(t_env **env, char *str)
{
	t_env		*pwd;
	t_env		*oldpwd;
	char		*tmp;

	pwd = find_list_env(*env, "PWD", 0);
	oldpwd = find_list_env(*env, "OLDPWD", 0);
	pwd_oldpwd(env, &pwd, &oldpwd);
	if (pwd && oldpwd)
	{
		tmp = oldpwd->value;
		oldpwd->value = pwd->value;
		pwd->value = tmp;
	}
	if (pwd)
	{
		tmp = pwd->value;
		if (!(pwd->value = ft_strdup(str)))
			exit(errno);
		free(tmp);
	}
}

static int		cd_minus(t_list *args, t_env **env, char **res)
{
	char		*str;

	str = find_data_in_env(*env, "OLDPWD", 0);
	if (!str || *str == '\0')
	{
		ft_putendl_fd("-minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	else if (!ft_strcmp(args->content, "--"))
		(*res) = ft_strdup(find_data_in_env(*env, "HOME", 0));
	else if (*(char*)args->content == '-' && \
	(ft_isalpha(*(char*)(args->content + 1)) || \
	*(char*)(args->content + 1) == '-'))
	{
		ft_putstr_fd("-minishell: cd: ", 2);
		ft_putchar_fd(*(char*)args->content, 2);
		ft_putchar_fd(*(char*)(args->content + 1), 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2);
		return (1);
	}
	if (!(*res))
		(*res) = ft_substr(str, 0, ft_strrchr(str, '\0') - str);
	return (0);
}

static int		arg_for_cd(t_list *args, t_env **env, char **res)
{
	char		*str;

	if (!(str = find_data_in_env(*env, "HOME", 0)) && \
	(!args || *(char*)args->content == '\0'))
	{
		ft_putendl_fd("-minishell: cd: HOME not set", 2);
		return (1);
	}
	if (!args || *(char*)args->content == '\0')
		(*res) = ft_strdup(str);
	else if (*(char*)args->content == '-')
	{
		if (cd_minus(args, env, res) > 0)
			return (1);
	}
	else
		(*res) = ft_strdup(args->content);
	if (!(*res))
		exit(errno);
	return (0);
}

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

static int 		get_pwd(char **pwd)
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
	{
		free(res);
		return (status);
	}
	if ((status = chdir_in_work(res)) > 0)
	{
		free(res);
		return (status);
	}
	if (get_pwd(&pwd) > 0)
	{
		free(res);
		free(pwd);
		return (0);
	}
	change_pwd(env, pwd);
	if (args && !ft_strncmp(args->content, "-", ft_strlen(args->content)))
		ft_putendl_fd(res, 1);
	free(res);
	free(pwd);
	return (status);
}
