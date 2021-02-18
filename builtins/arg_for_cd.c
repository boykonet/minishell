/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_for_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 00:51:36 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 00:51:36 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static void		pwd_oldpwd(t_env **env, t_env **pwd, t_env **oldpwd)
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

void			change_pwd(t_env **env, char *str)
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
	if (!ft_strcmp(args->content, "--"))
		(*res) = ft_strdup(find_data_in_env(*env, "HOME", 0));
	else if (!str || *str == '\0')
	{
		ft_putendl_fd("-minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	else if (*(char*)(args->content + 1) != ' ' && *(char*)(args->content + 1))
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

int				arg_for_cd(t_list *args, t_env **env, char **res)
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
