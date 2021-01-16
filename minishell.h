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
# include <string.h>
# include <errno.h>
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

typedef struct		s_data
{
	int 			argc;
	char 			**argv;
}					t_data;

typedef struct		s_params
{
	char			*cmd;
	t_list 			*args;
	int 			in;
	int 			out;
	int 			err;
	struct s_params	*next;
}					t_params;

//typedef struct		s_fd
//{
//	char			*redir_in;
//	char 			*redir_out;
//	char 			*redir_err;
//	char			*name_in;
//	char			*name_out;
//	char			*name_err;
//	int 			in;
//	int 			out;
//	int 			err;
//}					t_fd;

int					ft_cd(t_list *args, t_env **env, int *status);
char				*ft_pwd(char *pwd);
void				ft_echo(t_list **args, t_env *env, int return_value);
void				builtins(t_params *params, t_env **env, int *status);
void				del_content(void *content);
char				*find_data_in_env(t_env *env, char *needle, int serial_num);
//void 				init_fd(t_fd *fd);
t_params 			*init_params(t_params *params);
//void				*parser(t_list **tokens, t_params *params, t_fd *fd, int *status);
void				write_str(char *str, int fd, int flag);
t_env				*ft_lstnew_env(void *name, void *value);
t_env				*copy_envp_to_struct(char **envp);
//void				free_fd(t_fd *fd);
void				free_params(t_params *params);
void				free_string(char **str);
int					add_fd(char *in, char *redir);
int 				lexer(char **line, t_params **params, t_env *env);
int 				redirects(char *redir);
int					add_fd(char *file, char *redir);
int					getcharacter(int fd, char **line);
int 				error_handling(char *cmd, char *arg, char *error, int status);
void 				params_free(t_params **params, void (*del)(t_params *));
t_params			*params_new(void);
int 				check_redir(char **line);
char				*remove_spaces(char *line);
int 				redir(char **line, int *fd, int *status);
int 				open_fd(char **line, int *fd, int *status);
void 				ft_lstadd_back_env(t_env **env, t_env *new);

#endif
