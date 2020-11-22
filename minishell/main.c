/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:15:41 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/19 16:15:41 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void		free_string(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

void		free_params(t_params *params)
{
	if (params->args)
		free_string(params->args);
	if (params->command)
		free(params->command);
	if (params->flags)
		free(params->flags);
	if (params->redir)
		free(params->redir);
	if (params->name_fd)
		free(params->name_fd);
}

size_t		number_of_lines(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

char		**copy_str(char **str)
{
	char	**str_dup;
	size_t	i;
	size_t	j;
	size_t	str_size;

	i = 0;
	j = 0;
	str_size = number_of_lines(str);
	if (!(str_dup = malloc(sizeof(char*) * (str_size + 1))))
		return (NULL);
	str_dup[str_size] = NULL;
	while (str[i])
	{
		if (!(str_dup[j] = ft_strdup(str[i])))
		{
			free_string(str_dup);
			return (NULL);
		}
		i++;
		j++;
	}
	return (str_dup);
}

void		wait_line(char *str)
{
/* chochu chtoby bylo tak: ~/minishell/minishell$*/
//	char	*curr_location;
//	int		i;

	/* i = 0; */
	/* while (i < 2) */
	/* { */

	/* } */
//	write(1, curr_location, ft_strlen(curr_location));
	write(1, str, ft_strlen(str));
}

int				main(int argc, char **argv, char **envp)
{
	t_params	params;
	char		*line;
	char		*curr;
	char		**envp_dupl;
	int			ch;

	if (!(envp_dupl = copy_str(envp)))
		return (-1);
	while (TRUE)
	{
		wait_line("minishell$ ");
		if (get_next_line(0, &line) < 0)
			return (-1);
		curr = line;
		while (*curr)
		{
			printf("%c", *curr);
			curr++;
			init_params(&params);
/*			ch = parser(&params, &curr);
			builtins(&params, ch);*/
//			free_params(&params);
		}
		printf("\n");
		free(line);
	}
	return (0);
}
