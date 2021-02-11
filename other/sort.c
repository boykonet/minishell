/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:41:23 by snaomi            #+#    #+#             */
/*   Updated: 2021/02/11 08:42:56 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"

static void		swap(char **a, char **b)
{
	char		*t;

	t = *a;
	*a = *b;
	*b = t;
}

static int		relative_position(char **arr, int low, int high)
{
	char		*pivot;
	int			i;
	int			j;

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

void			quicksort(char **arr, int low, int high)
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
