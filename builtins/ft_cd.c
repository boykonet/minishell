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

void		change_pwd(t_env **env, char *str)
{
	t_env	*new;
	t_env	*pwd;
	t_env	*oldpwd;
	char	*tmp;

	pwd = find_list_env(*env, "PWD", 0);
	oldpwd = find_list_env(*env, "OLDPWD", 0);
	if (!pwd)
	{
		new = ft_lstnew_env(ft_strdup("PWD"), ft_strdup(""));
		if (!new->name || !new->value)
			exit(errno);
		ft_lstadd_back_env(env, new);
		pwd = find_list_env(*env, "PWD", 0);
	}
	if (!oldpwd)
	{
		new = ft_lstnew_env(ft_strdup("OLDPWD"), ft_strdup(""));
		if (!new->name || !new->value)
			exit(errno);
		ft_lstadd_back_env(env, new);
		oldpwd = find_list_env(*env, "OLDPWD", 0);
	}
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

char		*cd_minus(t_list *args, t_env **env)
{
	char	*str;
	char	*res;

	res = NULL;
	str = find_data_in_env(*env, "OLDPWD", 0);
	if (!str || *str == '\0')
	{
		ft_putendl_fd("-minishell: cd: OLDPWD not set", 2);
		return (NULL);
	}
	else if (!ft_strcmp(args->content, "--"))
		res = ft_strdup(find_data_in_env(*env, "HOME", 0));
	else if (*(char*)args->content == '-' && (ft_isalpha(*(char*)(args->content\
			+ 1)) || *(char*)(args->content + 1) == '-'))
	{
		ft_putstr_fd("-minishell: cd: ", 2);
		ft_putchar_fd(*(char*)args->content, 2);
		ft_putchar_fd(*(char*)(args->content + 1), 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2);
		return (NULL);
	}
	if (!res)
		res = ft_substr(str, 0, ft_strrchr(str, '\0') - str);
	return (res);
}

char		*arg_for_cd(t_list *args, t_env **env)
{
	char	*res;
	char	*str;

	if (!args || *(char*)args->content == '\0')
	{
		str = find_data_in_env(*env, "HOME", 0);
		res = ft_strdup(str);
	}
	else if (*(char*)args->content == '~')
	{
		str = find_data_in_env(*env, "HOME", 0);
		res = ft_strjoin(str, ((args->content) + 1));
	}
	else if (*(char*)args->content == '-')
	{
		if (!(res = cd_minus(args, env)))
			return (NULL);
	}
	else
		res = ft_strdup(args->content);
	if (!res)
		exit(errno);
	return (res);
}

int			ft_cd(t_list *args, t_env **env, int fd)
{
	char	*res;
	char	*pwd;

	pwd = NULL;
	if (!(res = arg_for_cd(args, env)))
		return (1);
	if ((chdir(res) < 0))
	{
		ft_putstr_fd("-minishell: cd: ", 2);
		ft_putstr_fd(res, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		free(res);
		return (1);
	}
	ft_pwd(&pwd);
	change_pwd(env, pwd);
	if (args && !ft_strncmp(args->content, "-", ft_strlen(args->content)))
		ft_putendl_fd(res, fd);
	free(res);
	free(pwd);
	return (0);
}
