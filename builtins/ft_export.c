/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:34:02 by snaomi            #+#    #+#             */
/*   Updated: 2021/02/09 15:31:59 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"
#include "builtins.h"

void			form_export(char **str, int len)
{
	int		k;
	int		i;

	k = 0;
	while (k < len)
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while (str[k][i])
		{
			ft_putchar_fd(str[k][i++], 1);
			if (str[k][i - 1] == '=')
				break ;
		}
		ft_putchar_fd('"', 1);
		while (str[k][i] != '\0')
			ft_putchar_fd(str[k][i++], 1);
		ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		k++;
	}
}

static int		relative_position(char **arr, int low, int high)
{
	char	*pivot;
	int		i;
	int		j;

	j = low;
	i = low - 1;
	pivot = arr[high];
	while (j <= high)
	{
		if (ft_strcmp(arr[j], pivot) < 0)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

static void		quicksort(char **arr, int low, int high)
{
	int			index;

	index = 0;
	if (low < high)
	{
		index = relative_position(arr, low, high);
		quicksort(arr, low, index - 1);
		quicksort(arr, index + 1, high);
	}
}

void 			print_export(t_env *buf)
{
	int		len;
	char	**arr;

	len = ft_lstsize_env(buf);
	arr = convert_env_to_arr(buf);
	quicksort(arr, 0, len - 1);
	form_export(arr, len);
	free_string(arr);
	return ;
}

int				ft_export(t_env **env, t_params *argv)
{
	t_env	*random;
	t_env	*buf;
	int		status;
	t_list	*smth;

	buf = *env;
	status = 0;
	smth = argv->args;
	while (smth->next)
	{
		smth = smth->next;
		if (check_word(smth))
		{
			random = new_item(smth);
			while (buf)
			{
				// add_if_found(buf, random);
				if (!ft_strcmp(random->name, buf->name))
				{
					if (random->value && *random->value != '\0')
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
			buf = *env;
		}
		else
			status = print_notification(argv, smth);
	}
	if (!ft_strncmp(argv->args->content, "export", 6) && !argv->args->next)
		print_export(buf);
	return (status);
}
