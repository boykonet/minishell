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

# define TRUE 1
# define LLONGMAX 9223372036854775807ULL

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_params
{
	t_list			*args;
	int				in;
	int				out;
	int				err;
	int 			pipe_semic;
	struct s_params	*next;
}					t_params;

typedef struct 		s_lexic
{
	int 			quotes;
	int 			escaping;
	int 			status;
}					t_lexic;

typedef struct		s_parser
{
	t_params		*params;
	t_env			*env;
	char 			**copy_line;
	int				status;
	int				exit_status;
	int				quotes;
	int 			dollar_flag;
	int 			pipe_semic;
	int 			escaping;
}					t_parser;

typedef struct 		s_pipes
{
	int 			lpipe[2];
	int 			rpipe[2];
	pid_t			*childpid;
	int 			size_params;
	int 			position;
}					t_pipes;

typedef struct		s_d
{
	t_params		*params;
	t_env			*env;
	char			**argv;
	char			*line;
	char			*folder;
	char			*username;
	int				origfd[2];
	int				argc;
	int				exit_status;
	int				flag;
}					t_d;

#endif
