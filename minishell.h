/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:05:06 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/19 14:05:06 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define TRUE	1
# define FALSE	0

typedef struct		s_params
{
	char			**flags;
	char			**args;
	char			*command;
	char			*redir;
	char			*name_fd;
	char			*error;
}					t_params;

/* typedef struct		s_data */
/* { */
/* 	t_list			*envp_dupl; */
/* 	/1* int				envp_size; *1/ */
/* 	/1* int				redir_left; *1/ */
/* 	/1* int				redir_rigth; *1/ */
/* 	/1* int				redir_double_rigth; *1/ */
/* }					t_data; */

/*typedef enum	e_ch
{
	A = 0,
	B
}				t_ch;

t_ch flag;


flag = A;

flag = B;*/

#endif
