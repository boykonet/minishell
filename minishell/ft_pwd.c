/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:31:27 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/19 15:31:27 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ft_pwd(char *pwd)
{
	if (!(pwd = getcwd(NULL, 0)))
		return (NULL);
	return (pwd);
}

int		main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_str	s_str;
	char	*arg[4] = {
	"pwd",
	">>",
	"file.txt",
	NULL };
	int		fd;

	if (!ft_strncmp(s_str.redir, "<", 1))
		data.redir_left = 1;

	else if (!ft_strncmp(s_str.redir, ">", 1))
		data.redir_rigth = 1;

	else if (!ft_strncmp(s_str.redir, ">>", 2))
		data.redir_double_rigth = 1;

	if (data.redir_double_rigth == 1)
		if ((fd = open(s_str.name_fd, O_CREAT | O_RDWR | O_APPEND, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (-1);
	else if (data.redir_rigth == 1)
		if ((fd = open(s_str.name_fd, O_CREAT | O_RDWR | O_TRUNC, \
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (-1);
	else if (data.redir_left == 1)
		data.redir_left = 1; /* ya ne znau cho etot redirect delaet */

	ft_pwd(pwd);
	close(fd);
}
