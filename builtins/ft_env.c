/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:04:27 by snaomi            #+#    #+#             */
/*   Updated: 2021/01/27 02:34:48 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 		print_env(char **str, int len)
{
	int k;
	int i;

	k = 0;
	while(k < len)
	{
		i = 0;
		while (str[k][i] != '\0')
			ft_putchar_fd(str[k][i++], 1);
		ft_putchar_fd('\n', 1);
		k++;
	}
}

int		ft_env(t_env **env, t_params *argv)
{
	int 	i;
	int 	len;
	t_env 	*buf;
	char	**arr;

	i = 0;
	buf = *env;
	if (argv->args->next)
	{
		argv->args= argv->args->next;
		ft_putstr_fd("env: `", 1);
		ft_putstr_fd(argv->args->content, 1);
		ft_putstr_fd("`: No such file or directory", 1);
		ft_putchar_fd('\n', 1);
	}	
	else if (!ft_strncmp(argv->args->content, "env", ft_strlen(argv->args->content)))
	{
		len = ft_lstsize_env(buf);
		arr = from_list_to_arr(buf, len);
		print_env(arr, len);
	}
	return (0);
}
