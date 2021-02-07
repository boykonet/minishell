/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:34:02 by snaomi            #+#    #+#             */
/*   Updated: 2021/02/07 15:51:22 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"

void			print_export(char **str, int len)
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

static void		swap(char **a, char **b)
{
	char		*t;

	t = *a;
	*a = *b;
	*b = t;
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

int				ft_export(t_env **env, t_params *argv)
{
	char	**arr;
	t_env	*random;
	t_env	*buf;
	int		len;
	int		status;

	buf = *env;
	status = 0;
	while (argv->args->next)
	{
		argv->args = argv->args->next;
		if (check_word(argv->args))
		{
			random = new_item(argv->args);
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
			buf = *env;
		}
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(argv->args->content, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
	}
	if (!ft_strncmp(argv->args->content, "export", 6))
	{
		len = ft_lstsize_env(buf);
		arr = convert_env_to_arr(buf);
		quicksort(arr, 0, len - 1);
		print_export(arr, len);
		free_string(arr);
	}
	return (status);
}
