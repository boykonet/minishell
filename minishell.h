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
# include "./gnl/get_next_line.h"
# include "./libft/libft.h"

# define TRUE	1
# define FALSE	0

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;	
}					t_env;

typedef struct		s_params
{
	char			**args;
	char			*flags;
	char			*command;
	char			*redir;
	char			*name_fd;
	char			*error;
}					t_params;

/*typedef enum	e_ch
{
	A = 0,
	B
}				t_ch;

t_ch flag;


flag = A;

flag = B;*/

#endif
