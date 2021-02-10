/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_notification.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.r       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 19:03:52 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/09 19:03:52 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				print_notification(t_params *argv, t_list *smth)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv->args->content, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(smth->content, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}
