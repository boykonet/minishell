/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 06:09:44 by snaomi            #+#    #+#             */
/*   Updated: 2020/11/23 14:55:15 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	calculate_str(char const *s1, char c)
{
	int i;

	i = 0;
	while (*s1 != '\0')
	{
		while (*s1 != '\0' && *s1 == c)
			s1++;
		if (*s1 != '\0')
			i++;
		while (*s1 != '\0' && *s1 != c)
			s1++;
	}
	return (i);
}

static int	calculate_length(char const *s1, char c)
{
	int i;

	i = 0;
	while (*s1 != '\0' && *s1 == c)
		s1++;
	while (*s1 != c && *s1 != '\0')
	{
		i++;
		s1++;
	}
	return (i);
}

static char	*record_string(char *dest, char const *src, char c)
{
	while (*src != '\0' && *src == c)
		src++;
	while (*src != '\0' && *src != c)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest);
}

static void		*free_arr(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (0);
}

char		**ft_split_env(char const *s, char c)
{
	char	**temp;
	size_t	length_str;
	int		index_str;
	// int		number_str;

	if (s == NULL)
		return (NULL);
	index_str = 0;
	// number_str = calculate_str(s, c);
	if (!(temp = (char**)malloc(sizeof(char*) * 2)))
		return (NULL);
	while (index_str < 1)
	{
		length_str = calculate_length(s, c);
		if (!(temp[index_str] = (char*)malloc(sizeof(char) * (length_str + 1))))
			return (free_arr(temp));
		record_string(temp[index_str], s, c);
		while (*s == c && *s != '\0')
			s++;
		s += length_str;
		index_str++;
	}
	s++;
	length_str = calculate_length(s, '\0');
	if (!(temp[index_str] = (char*)malloc(sizeof(char) * (length_str + 1))))
		return (free_arr(temp));
	record_string(temp[index_str++], s, '\0');
	temp[index_str] = NULL;
	return (temp);
}
