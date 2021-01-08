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

int			ft_cd(char *args, char **home, char **pwd_curr, char **old_pwd)
{
	char	*pwd;
	char	*str;
	char	*start;
	char	*end;
	int		a;

	pwd = NULL;
	str = NULL;
	start = NULL;
	end = NULL;
	if (!ft_strncmp(args, "~", 1) || *args == '\0')
	{
		start = ft_strchr(*home, '/');
		end = ft_strrchr(*home, '\"');
		str = ft_substr(start, 0, end - start);
	}
	else if (!ft_strncmp(args, "-", 1))
	{
		start = ft_strchr(*old_pwd, '/');
		end = ft_strrchr(*old_pwd, '\"');
		str = ft_substr(start, 0, end - start);
	}
	else
		str = ft_strdup(args);

	/* printf("%s\n", str); */
	/* a = chdir(str); */
	if ((a = chdir(args) < 0))
		return (-1);
	/* printf("a = [%d]\n", a); */
	/* printf("%d\n", errno); */
	/* printf("%s\n", strerror(errno)); */
	if (!(pwd = ft_pwd(pwd)))
		return (-1);
	change_pwd(pwd_curr, old_pwd, pwd);
	free(pwd);
	free(str);
	return (0);
}