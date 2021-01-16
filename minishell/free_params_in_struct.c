/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_params_in_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:55:27 by gkarina           #+#    #+#             */
/*   Updated: 2020/12/17 22:55:27 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void 			env_free(t_env **env, void (*del)(t_env *))
{
	t_env		*curr;

	while ((*env) != NULL)
	{
		curr = (*env)->next;
		if (del)
			(*del)((*env));
		free((*env));
		(*env) = curr;
	}
}

void 			params_free(t_params **params, void (*del)(t_params *))
{
	t_params	*curr;

	while ((*params) != NULL)
	{
		curr = (*params)->next;
		if (del)
			(*del)((*params));
		free((*params));
		(*params) = curr;
	}
}

void			free_string(char **str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

void 			free_data(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->argv)
		free_string(data->argv);
	if (data->params)
		params_free(&data->params, free_params);
	if (data->env)
		env_free(&data->env, del_env_content);
}