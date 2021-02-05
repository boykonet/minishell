/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 17:52:02 by gkarina           #+#    #+#             */
/*   Updated: 2021/01/31 17:52:02 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"

void			write_username_folder(t_env *env, char **username, char **folder)
{
	char 		*line;

	if ((line = find_data_in_env(env, "USER", 0)))
	{
		if (*username)
			free(*username);
		if (!(*username = ft_strdup(line)))
			exit(errno);
	}
	if ((line = find_data_in_env(env, "PWD", 0)))
	{
		if (*folder)
			free(*folder);
		if ((ft_strcmp(find_data_in_env(env, "HOME", 0), line)))
			*folder = ft_strdup(ft_strrchr(line, '/'));
		else
			*folder = ft_strdup(line);
		if (!*folder)
			exit(errno);
	}
}

char			*prompt_line(t_env *env, char **username, char **folder)
{
	char 		*line;
	char 		*res;

	write_username_folder(env, username, folder);
	if (ft_strlen(*folder) == 1)
		line = ft_strjoin("\e[1;36m", *folder);
	else if (!(ft_strcmp(find_data_in_env(env, "HOME", 0), *folder)))
		line = ft_strdup("\e[1;36m~");
	else
		line = ft_strjoin("\e[1;36m", *folder + 1);
	if (!line)
		exit(errno);
	if (!(res = ft_strjoin(line, " ")))
		exit(errno);
	free(line);
	if (!(line = ft_strjoin(res, *username)))
		exit(errno);
	free(res);
	if (!(res = ft_strjoin(line, "\e[0m$ ")))
		exit(errno);
	free(line);
	return (res);
}

//void			print_prompt_line(t_env *env, char **user_name, char **folder)
//{
//	char		*str;
//
//	str = prompt_line(env, user_name, folder);
//	ft_putstr_fd(str, 1);
//	free(str);
//}

void            print_prompt_line(t_d *data, int signo)
{
	static t_d *temp;
	char        *str;
	if (temp == NULL)
		temp = data;
	if (signo != 0 && temp->flag == 0)
		write(1, "\b\b  \b\b", ft_strlen("\b\b  \b\b") + 1);
	if ((signo == SIGINT && temp->flag == 0) || (signo == SIGINT && temp->flag == 1))
		write(1, "\n", 1);
	if (signo == 0 || (signo == SIGINT && temp->flag == 0))
	{
		str = prompt_line(temp->env, &temp->username, &temp->folder);
		ft_putstr_fd(str, 1);
		free(str);
	}
	if (signo == SIGQUIT && temp->flag == 1)
		write(1, "Quit: 3\n", ft_strlen("Quit: 3\n") + 1);
}
