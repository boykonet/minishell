/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:25:42 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/22 15:25:42 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			meta(unsigned char *meta, int shift, int num)
{
	if ((*meta & (1 << shift)) != num)
		*meta |= (1 << shift);
	else
		return (0);
	return (1);
}
