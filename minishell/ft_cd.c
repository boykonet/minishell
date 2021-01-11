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
#include <errno.h>
#include <string.h>

void		change_pwd(char **pwd_curr, char **old_pwd, char *pwd)
{
	char	*tmp;

	tmp = *old_pwd;
	*old_pwd = ft_strdup(*pwd_curr);
	/* printf("%s\n", *old_pwd); */
	free(tmp);

	tmp = *pwd_curr;
	*pwd_curr = ft_strdup(pwd);
	free(tmp);
	/* printf("%s\n", *pwd_curr); */
}

int			ft_cd(char **args, t_env *env, int *status)
{
	char	*pwd;
	char	*str;

	str = NULL;
	if (!ft_strncmp(args[0], "~", ft_strlen(args[0])) || *args[0] == '\0')
	{
		find_data_in_env(env, "HOME", &str, 0);
		str = ft_substr(str, 0, ft_strrchr(str, '\0') - str);
	}
	else if (!ft_strncmp(args[0], "-", ft_strlen(args[0])))
	{
		find_data_in_env(env, "OLDPWD", &str, 0);
		str = ft_substr(str, 0, ft_strrchr(str, '\0') - str);
	}
	else
		str = ft_strdup(args[0]);
	if ((chdir(str) < 0))
	{
		free(str);
		return (-1);
	}
	free(str);
	if (!(pwd = ft_pwd(pwd)))
		return (-1);
	change_pwd(pwd_curr, old_pwd, pwd);
	free(pwd);
	return (0);
}