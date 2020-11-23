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

char		*ft_pwd(char *pwd);

void		change_pwd(char **pwd_curr, char **old_pwd, char *pwd)
{
	char	*tmp;

	tmp = *old_pwd;
	*old_pwd = ft_strjoin("OLD", *pwd_curr);
	/* printf("%s\n", *old_pwd); */
	free(tmp);

	tmp = *pwd_curr;
	*pwd_curr = ft_strjoin("PWD=\"", pwd);
	free(tmp);
	tmp = *pwd_curr;
	*pwd_curr = ft_strjoin(*pwd_curr, "\"");
	/* printf("%s\n", *pwd_curr); */
	free(tmp);
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
		return (a);
	/* printf("a = [%d]\n", a); */
	/* printf("%d\n", errno); */
	/* printf("%s\n", strerror(errno)); */
	if (!(pwd = ft_pwd(pwd)))
		return (NULL);
	change_pwd(pwd_curr, old_pwd, pwd);
	free(pwd);
	free(str);
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	t_list	*args;
	char	*str;
	char	*pwd_curr;
	char	*home;
	char	*old_pwd;

	pwd_curr = ft_strdup("PWD=\"/Users/boykonet/Desktop/minishell/minishell\"");
	old_pwd = ft_strdup("OLDPWD=\"/Users/boykonet/Desktop/minishell\"");
	home = ft_strdup("HOME=\"/Users/boykonet\"");
	args = ft_lstnew(ft_strdup("-"));
	str = ft_cd(args->content, &home, &pwd_curr, &old_pwd);
	printf("<%s>\n", home);
	printf("<%s>\n", pwd_curr);
	printf("<%s>\n", old_pwd);
	
//	printf("%s\n", str);
}
