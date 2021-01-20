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

int			ft_cd(t_list *args, t_env **env)
{
	char 	*res;
	char	*str;
	t_env	*new;

	str = NULL;
	res = NULL;
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
		str = find_data_in_env(*env, "OLDPWD", 0);
		if (!str)
		{
			ft_printf("-minishell: cd: OLDPWD not set\n");
			return (1);
		}
		res = ft_substr(str, 0, ft_strrchr(str, '\0') - str);
	}
	else
		res = ft_strdup(args->content);
	if ((chdir(res) < 0))
	{
		ft_printf("cd: %s: %s\n", res, strerror(errno));
		free(res);
		return (1);
	}
	free(res);
	ft_pwd(&res);
	change_pwd(env, res);
	free(res);
	return (0);
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