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

# define TRUE	1
# define FALSE	0

typedef struct	s_data
{
	char		**envp_dupl;
	int			envp_size;
	int			redir_left;
	int			redir_rigth;
	int			redir_double_rigth;
}				t_data;

/*typedef enum	e_ch
{
	A = 0,
	B
}				t_ch;

t_ch flag;


flag = A;

flag = B;*/

#endif
