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

int 		change_pwd(t_env **env, char *str)
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
	if (oldpwd && !oldpwd->value)
	{
		oldpwd->value = ft_strdup(pwd->value);
//	else if (oldpwd)
	}
	else
	{
		tmp = oldpwd->value;
		oldpwd->value = pwd->value;
		pwd->value = tmp;
	}
	tmp = pwd->value;
	pwd->value = ft_strdup(str);
	free(tmp);
	return (1);
}

void 		ft_lstadd_back_env(t_env **env, t_env *new)
{
	t_env	*current;
	t_env	*prev;

	current = (*env);
	prev = (*env);
	if (current == NULL)
		(*env) = new;
	else
	{
		while (current != NULL)
		{
			prev = current;
			current = current->next;
		}
		prev->next = new;
	}
}

int			ft_cd(t_list *args, t_env **env, int *status)
{
	char	*str;

	str = NULL;
//	if (!ft_strncmp(args->content, "~", 1) || *(args->content) == '\0')
//	{
//		find_data_in_env(env, "HOME", &str, 0);
//		str = ft_substr(str, 0, ft_strrchr(str, '\0') - str);
//	}
//	if (!ft_strncmp(args->content, "-", ft_strlen(args->content)))
//	{
//		find_data_in_env(*env, "OLDPWD", &str, 0);
//		if (!str)
//		{
//			if (!(new = ft_lstnew_env("OLDPWD", )))
//			ft_lstadd_back_env(env, new);
//			return (0);
//		}
//		str = ft_substr(str, 0, ft_strrchr(str, '\0') - str);
//	}
//	else
	str = ft_strdup(args->content);
	if ((chdir(str) < 0))
	{
		error_handling("cd", str, 2, 1);
		free(str);
		return (-1);
	}
	free(str);
	str = ft_pwd(str);
	change_pwd(env, str);
	free(str);
	return (1);
}

//int 		main(int argc, char **argv, char **envp)
//{
//	t_env	*env;
//	t_list	*lst;
//	int 	status;
//
//	status = 0;
//	if (!(env = copy_envp_to_struct(envp)))
//		return (-1);
//	lst = ft_lstnew(ft_strdup(".."));
//	ft_cd(lst, &env, &status);
//	while (env)
//	{
//		printf("%s=%s\n", env->name, env->value);
//		env = env->next;
//	}
//	return (0);
//}