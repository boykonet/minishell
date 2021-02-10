/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:29:43 by snaomi            #+#    #+#             */
/*   Updated: 2021/02/07 15:34:32 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		arg_exit(char *str, int *neg, unsigned long long *long_num, \
						int *overflow)
{
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*neg = -1;
		str++;
	}
	while (!*overflow && *str && *str >= '0' && *str <= '9')
	{
		*long_num = *long_num * 10 + *str++ - '0';
		if ((*neg == 1 && *long_num > LLONGMAX) || \
			(*neg == -1 && *long_num > (LLONGMAX + 1)))
			*overflow = 1;
	}
	if (*str && *str != ' ' && !ft_isdigit(*str))
		*overflow = 1;
}

static int		exit_error(char *str, int *error_status, int overflow,\
				int many_arg)
{
	int		status;

	status = 0;
	if (overflow)
	{
		ft_putstr_fd("-minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		status = 255;
		*error_status = 2;
	}
	else if (many_arg)
	{
		ft_putendl_fd("-minishell: exit: too many arguments", 2);
		status = 1;
		*error_status = 2;
	}
	return (status);
}

int				ft_exit(t_list *args, int *error_status)
{
	unsigned long long	long_num;
	int					neg;
	int					answ;
	int					overflow;
	int					many_arg;

	neg = 1;
	overflow = 0;
	long_num = 0;
	many_arg = 0;
	answ = 0;
	*error_status = 1;
	if (args && args->next)
		many_arg = 1;
	if (args)
		arg_exit(args->content, &neg, &long_num, &overflow);
	ft_putendl_fd("exit", 1);
	if (args && (answ = exit_error(args->content, error_status, \
	overflow, many_arg)) > 0)
		long_num = answ;
	return (((unsigned char)((long long)long_num * neg)));
}
