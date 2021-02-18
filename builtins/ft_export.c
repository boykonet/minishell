/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:34:02 by snaomi            #+#    #+#             */
/*   Updated: 2021/02/11 18:08:47 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "builtins.h"

static void		print_comma(char **str, int k, int i)
{
	if (str[k][i])
	{
		ft_putchar_fd('"', 1);
		while (str[k][i] != '\0')
			ft_putchar_fd(str[k][i++], 1);
		ft_putchar_fd('"', 1);
	}
	else if (str[k][i - 1] == '=')
	{
		ft_putchar_fd('"', 1);
		ft_putchar_fd('"', 1);
	}
	ft_putchar_fd('\n', 1);
}

static void		form_export(char **str, int len)
{
	int			k;
	int			i;

	k = 0;
	while (k < len)
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while ((i == 0 && str[k][i]) || (str[k][i] && str[k][i - 1] != '='))
		{
			ft_putchar_fd(str[k][i], 1);
			i++;
		}
		print_comma(str, k, i);
		k++;
	}
}

static void		print_export(t_env *buf)
{
	int			len;
	char		**arr;

	len = ft_lstsize_env(buf);
	arr = convert_env_to_arr(buf);
	quicksort(arr, 0, len - 1);
	form_export(arr, len);
	free_string(arr);
}

static int		add_it(t_env *buf, t_list *smth, t_env **env)
{
	t_env		*random;

	random = new_item(smth);
	while (buf)
	{
		if (!ft_strcmp(random->name, buf->name))
		{
			if (random->value)
			{
				buf->value = random->value;
				return (0);
			}
			else
				return (0);
		}
		buf = buf->next;
	}
	ft_lstadd_back_env(env, random);
	return (0);
}

int				ft_export(t_env **env, t_params *argv)
{
	int			status;
	t_list		*smth;
	t_env		*buf;

	status = 0;
	buf = *env;
	smth = argv->args;
	while (smth->next)
	{
		smth = smth->next;
		if (check_word(smth) && !(add_it(buf, smth, env)))
			continue ;
		else
			status = print_notification(argv, smth);
	}
	if (!ft_strncmp(argv->args->content, "export", 6) && !argv->args->next)
		print_export(buf);
	return (status);
}
