/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:04:27 by snaomi            #+#    #+#             */
/*   Updated: 2021/02/09 14:57:20 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"

static void		print_env(char **str, int len)
{
	int			k;
	int			i;

	k = 0;
	while (k < len)
	{
		i = 0;
		while (str[k][i] != '\0')
			ft_putchar_fd(str[k][i++], 1);
		ft_putchar_fd('\n', 1);
		k++;
	}
}

char		**prepare_env_to_arr(t_env *env)
{
	int		i;
	char	**arr;
	char	*tmp;

	i = ft_lstsize_env(env);
	if (!(arr = ft_calloc(i + 1, sizeof(char*))))
		exit(errno);
	i = 0;
	while (env)
	{
		if (env->value && *env->value != '\0')
		{
			if (!(tmp = ft_strjoin(env->name, "=")))
				exit(errno);
			if (!(arr[i] = ft_strjoin(tmp, env->value)))
				exit(errno);
			free(tmp);
			i++;
		}
		env = env->next;
	}
	return (arr);
}

int				ft_env(t_env **env, t_params *argv)
{
	t_env		*buf;
	char		**arr;
	int			len;
	int			status;

	buf = *env;
	status = 0;
	len = 0;
	if (argv->args->next)
	{
		argv->args = argv->args->next;
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv->args->content, 2);
		ft_putendl_fd(": No such file or directory", 2);
		status = 127;
	}
	else if (!ft_strncmp(argv->args->content, "env", 3))
	{
		arr = prepare_env_to_arr(buf);
		while(arr && arr[len])
			len++;
		print_env(arr, len);
		free_string(arr);
	}
	return (status);
}
