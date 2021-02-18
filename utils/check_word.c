/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 03:17:01 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 03:17:01 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

int			check_word(t_list *list)
{
	t_env	*random;
	char	*buf;
	int		i;
	int		len;

	i = 0;
	random = new_item(list);
	buf = random->name;
	len = ft_strlen(buf);
	while (i < len)
	{
		if ((i == 0 && !ft_isalpha(buf[i]) && buf[i] != 95) || \
		(i != 0 && !ft_isalnum(buf[i]) && !(buf[i] == 95)))
		{
			free_env_element(random);
			return (0);
		}
		i++;
	}
	free_env_element(random);
	if (len == 0)
		return (0);
	return (1);
}
