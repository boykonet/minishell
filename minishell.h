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
	char			*cmd;
	char 			*args;
	char			*redir_in;
	char 			*redir_out;
	char 			*redir_err;
	char			*name_in;
	char 			*name_out;
	char 			*name_err;
}					t_params;

typedef struct		s_fd
{
	char			*name_in;	/* 0 */
	char			*name_out;	/* 1 */
	char			*name_err;	/* 2 */
}					t_fd;

int					ft_cd(char *args, char **home, char **pwd_curr, char **old_pwd);
void				builtins(t_params *params, char **home, char **pwd_curr, char **old_pwd);
void				del_content(void *content);
void				find_data_in_env(t_env *env, char *needle, char **result, int serial_num);
char				*ft_pwd(char *pwd);
void				init_fd(t_fd *fd);
void				init_params(t_params *params);
t_list				*parser(t_list *tokens, t_fd *fd);
void				write_str(char *str, int fd, int flag);
t_env				*ft_lstnew_env(void *name, void *value);
t_env				*copy_envp_to_struct(char **envp);
void				free_fd(t_fd *fd);
void				free_params(t_params *params);
void				free_string(char **str);
int					add_fd(char *in, char *redir);
t_list				*lexer(char **line, t_env *env);

#endif
