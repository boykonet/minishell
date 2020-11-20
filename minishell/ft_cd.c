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

char		*ft_cd(t_list *args, char *home, char *pwd_curr, char *old_pwd)
{
	char	*pwd;
	char	*str;
	char	*start;
	char	*end;

	pwd = NULL;
	str = NULL;
	start = NULL;
	end = NULL;
	if (!(pwd = ft_pwd(pwd)))
		return (NULL);
	if (!ft_strncmp(args->content, "/", 1))
		str = ft_strdup("/");
	else if (!ft_strncmp(args->content, "..", 2) || \
			!ft_strncmp(args->content, "../", 3))
	{
		str = ft_substr(pwd, 0, ft_strrchr(pwd, '/') - pwd);
		free(pwd);
	}
	else if (!ft_strncmp(args->content, ".", 1))
		str = pwd;
	else if (!ft_strncmp(args->content, "~", 1) || \
			args->content == NULL)
	{
		start = ft_strchr(home, '/');
		end = ft_strrchr(home, '"') - 1;
		str = ft_substr(start, 0, end - start);
	}
	if (chdir(str) < 0)
		return (NULL);
	return (str);
}

int		main(int argc, char **argv, char **envp)
{
	t_list	args;
	char	*str;
	char	*pwd;
	char	*home;
	char	*oldpwd;

	pwd = "PWD=\"/Users/boykonet/Desktop/minishell/minishell\"";
	oldpwd = "OLDPWD=\"/Users/boykonet/Desktop/minishell\"";
	home = "HOME=\"/Users/boykonet\"";
	argc->content = ft_lstnew(ft_strdup("../"));
	if (!(str = ft_cd(args, home, pwd, oldpwd)))
		return (-1);
	printf("%s\n", str);
}
