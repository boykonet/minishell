/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:05:19 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/18 21:05:19 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_echo(t_list **args, char *flags, t_env *env)
{
	t_list	*curr;
	t_env	*env_dupl;
	char	*tmp;
	char	*str;
	int		i;

	tmp = NULL;
	i = 0;
	curr = (*args);
	while (curr)
	{
		while (tmp = ft_strnstr(curr->content, "$?", ft_strlen(curr->content)))
		{
			curr->content = ft_substr(curr->content, 0, tmp - curr->content);

			curr->content = ft_strdup(ft_atoi());
			free(tmp);
			break ;
		}
		if ((tmp = ft_strchr(curr->content, '$')))
		{
			if (!ft_strncmp(tmp, "$?", ft_strlen(curr)))
				{
					tmp = ft_substr(curr->content, 0, i);
					
					curr->content = ft_strjoin(curr->contentft_atoi(return_value);
					free(tmp);
					break ;
				}
		}
		while (curr->content[i])
		{
			if (*curr->content == '$')
			{
				if (!ft_strncmp(curr->content, "$?", ft_strlen(curr)))
				{
					tmp = ft_substr(curr->content, 0, i);
					
					curr->content = ft_strjoin(curr->contentft_atoi(return_value);
					free(tmp);
					break ;
				}
			while (curr->content[i] != '$' || curr->content[i] != '\0')
				i++;
			find_
		}
	}
	/* t_list	*curr; */
	/* char	*result; */
	/* char	*tmp; */
	/* int		back_slash; */
	/* int		i; */

	/* i = 0; */
	/* tmp = NULL; */
	/* back_slash = 0; */
	/* curr = params->args; */
	/* if (!ft_strncmp(params->flags, "n", 1)) */
	/* 	back_slash = 1; */
	/* if (!(result = ft_strdup(""))) */
	/* 	return (NULL); */
	/* while (curr) */
	/* { */
	/* 	tmp = result; */
	/* 	if (!(result = ft_strjoin(result, curr->content))) */
	/* 	{ */
	/* 		free(tmp); */
	/* 		free_params(params); */
	/* 		return (NULL); */
	/* 	} */
	/* 	/1* if (params->args_size - i == 0) *1/ */
	/* 	/1* 	write_str(curr->content, fd, 1); *1/ */
	/* 	/1* else *1/ */
	/* 	/1* 	write_str(curr->content, fd, 0); *1/ */
	/* 	curr = curr->next; */
	/* 	i++; */
	/* } */
	/* if (back_slash == 0) */
	/* 	write(fd, "\n", 1); */
	return (0);
}
