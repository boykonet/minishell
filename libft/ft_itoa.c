/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 19:03:18 by gkarina           #+#    #+#             */
/*   Updated: 2020/05/10 19:03:18 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_count(int n)
{
	int		number;
	int		count;

	count = 0;
	number = n;
	if (n == 0)
		count++;
	if (n < 0)
	{
		number = n * (-1);
		count++;
	}
	while (number != 0)
	{
		number = number / 10;
		count++;
	}
	return (count);
}

static char	*ft_itoa_logic(char *dst, int n, int count, int flag)
{
	char	*d;

	d = &dst[count];
	if (n < 0)
	{
		dst[0] = '-';
		n = n * (-1);
	}
	if (n != 0)
	{
		if (flag == 1)
		{
			dst[--count] = '0' + (n % 10) + 1;
			n = n / 10;
		}
		while (n != 0)
		{
			dst[--count] = '0' + (n % 10);
			n = n / 10;
		}
	}
	else
		dst[0] = '0';
	*d = '\0';
	return (dst);
}

char		*ft_itoa(int n)
{
	char	*dst;
	int		count;
	int		flag;

	flag = 0;
	if (n == -2147483648)
	{
		n = n + 1;
		flag = 1;
	}
	count = ft_itoa_count(n);
	if ((dst = (char*)malloc(sizeof(char) * (count + 1))) == NULL)
		return (NULL);
	ft_itoa_logic(dst, n, count, flag);
	return (dst);
}
