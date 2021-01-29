/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 21:04:27 by snaomi            #+#    #+#             */
/*   Updated: 2021/01/29 10:20:48 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"

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
	int 	len;
	t_env 	*buf;
	char	**arr;

	len = 0;
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
		len = ft_lstsize_env(*env);
		arr = convert_env_to_arr(buf);
		print_env(arr, len);
		free_string(arr);
	}
	return (0);
}
