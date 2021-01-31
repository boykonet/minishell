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

# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libs/libft/libft.h"
# include "../libs/printf/libftprintf.h"

# define TRUE 1

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_params
{
	t_list 			*args;
	int 			in;
	int 			out;
	int 			err;
	struct s_params	*next;
}					t_params;

typedef struct		s_d
{
	t_params		*params;
	t_env			*env;
	char 			**argv;
	char 			*line;
	char 			*folder;
	char 			*username;
	int 			argc;
	int 			exit_status;
}					t_d;

#endif
