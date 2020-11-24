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
	a = chdir(str);
	/* if ((a = chdir(args) < 0)) */
	/* 	return (a); */
	printf("a = [%d]\n", a);
	printf("%d\n", errno);
	printf("%s\n", strerror(errno));
	if (!(pwd = ft_pwd(pwd)))
		return (0);
	change_pwd(pwd_curr, old_pwd, pwd);
	free(pwd);
	free(str);
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_list	*args;
	t_env	*pwd_curr;
	t_env	*home;
	t_env	*old_pwd;

	env = ft_lstnew_env(ft_strdup("PWD"), ft_strdup("/Users/boykonet/Desktop/minishell/minishell"));
	env->next = ft_lstnew_env(ft_strdup("OLDPWD"), ft_strdup("/Users/boykonet/Desktop"));
	env->next->next = ft_lstnew_env(ft_strdup("PATH"), ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Library/Apple/usr/bin"));
	env->next->next->next = ft_lstnew_env(ft_strdup("HOME"), ft_strdup("/Users/boykonet"));

	if (!(pwd_curr = find_env_in_structs(env, "PWD")))
		return (-1);
	if (!(old_pwd = find_env_in_structs(env, "OLDPWD")))
		return (-1);
	if (!(home = find_env_in_structs(env, "HOME")))
		return (-1);

	printf("<%s=%s>\n", home->name, home->value);
	printf("<%s=%s>\n", pwd_curr->name, pwd_curr->value);
	printf("<%s=%s>\n", old_pwd->name, old_pwd->value);

	/* pwd_curr = ft_strdup("PWD=\"/Users/boykonet/Desktop/minishell/minishell\""); */
	/* old_pwd = ft_strdup("OLDPWD=\"/Users/boykonet/Desktop/minishell\""); */
	/* home = ft_strdup("HOME=\"/Users/boykonet\""); */
	args = ft_lstnew(ft_strdup("../libft/"));
	ft_cd(args->content, &home->value, &pwd_curr->value, &old_pwd->value);
	printf("<%s=%s>\n", home->name, home->value);
	printf("<%s=%s>\n", pwd_curr->name, pwd_curr->value);
	printf("<%s=%s>\n", old_pwd->name, old_pwd->value);
	
//	printf("%s\n", str);
}
