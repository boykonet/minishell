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
	pwd = getcwd(NULL, 0);
	return (pwd);
}

/* int		main(int argc, char **argv, char **envp) */
/* { */
/* 	t_data		data; */
/* 	t_params	params; */
/* 	char		*arg[4] = { */
/* 	"pwd", */
/* 	">>", */
/* 	"file.txt", */
/* 	NULL }; */
/* 	int		fd; */

/* 	/1* if (!ft_strncmp(params.redir, "<", 1)) *1/ */
/* 	/1* 	data.redir_left = 1; *1/ */

/* 	/1* else if (!ft_strncmp(params.redir, ">", 1)) *1/ */
/* 	/1* 	data.redir_rigth = 1; *1/ */

/* 	/1* else if (!ft_strncmp(params.redir, ">>", 2)) *1/ */
/* 	/1* 	data.redir_double_rigth = 1; *1/ */

/* 	fd = 1; */
/* 	if (!ft_strncmp(params.redir, ">>", 2)) */
/* 		if ((fd = open(params.name_fd, O_CREAT | O_RDWR | O_APPEND, \ */
/* 				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) */
/* 			return (-1); */
/* 	else if (!ft_strncmp(params.redir, ">", 1)) */
/* 		if ((fd = open(params.name_fd, O_CREAT | O_RDWR | O_TRUNC, \ */
/* 						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) */
/* 			return (-1); */
/* 	else if (!ft_strncmp(params.redir, "<", 1)) */
/* 		; /1* ya ne znau cho etot redirect delaet *1/ */

/* 	ft_pwd(pwd); */
/* 	close(fd); */
/* } */
