/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:30:25 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/19 15:30:25 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		change_pwd(t_env **env, char *str)
{
	t_env	*new;
	t_env	*pwd;
	t_env	*oldpwd;
	char 	*tmp;

	oldpwd = NULL;
	pwd = NULL;
	new = (*env);
	while (new)
	{
		if (!ft_strncmp(new->name, "PWD", ft_strlen(new->name)))
			pwd = new;
		else if (!ft_strncmp(new->name, "OLDPWD", ft_strlen(new->name)))
			oldpwd = new;
		new = new->next;
	}
	if (!pwd)
	{
		new = ft_lstnew_env(ft_strdup("PWD"), ft_strdup(""));
		if (!new->name || !new->value)
			exit(errno);
		ft_lstadd_back_env(env, new);
	}
	if (!oldpwd)
	{
		new = ft_lstnew_env(ft_strdup("OLDPWD"), ft_strdup(""));
		if (!new->name || !new->value)
			exit(errno);
		ft_lstadd_back_env(env, new);
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

char 		*cd_minus(t_env **env)
{
	char 	*str;
	char 	*res;

	str = find_data_in_env(*env, "OLDPWD", 0);
	if (!str)
	{
		ft_printf("-minishell: cd: OLDPWD not set\n");
		return (NULL);
	}
	res = ft_substr(str, 0, ft_strrchr(str, '\0') - str);
	return (res);
}

char 		*arg_for_cd(t_list *args, t_env **env)
{
	char 	*res;
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
	else if (!ft_strncmp(args->content, "-", ft_strlen(args->content)))
	{
		if (!(res = cd_minus(env)))
			return (NULL);
	}
	else
		res = ft_strdup(args->content);
	if (!res)
		exit(errno);
	return (res);
}

int			ft_cd(t_list *args, t_env **env)
{
	char 	*res;

	if (!(res = arg_for_cd(args, env)))
		return (1);
	if ((chdir(res) < 0))
	{
		ft_printf("-minishell: cd: %s: %s\n", res, strerror(errno));
		free(res);
		return (1);
	}
	free(res);
	ft_pwd(&res);
	change_pwd(env, res);
	free(res);
	return (0);
}