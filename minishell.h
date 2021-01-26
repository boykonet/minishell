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
# include "./libft/libft.h"
# include "./printf/libftprintf.h"

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
	int 			argc;
}					t_d;

int					ft_cd(t_list *args, t_env **env);
int					ft_pwd(char **pwd);
int					ft_echo(t_list *args, int fd);
int                 ft_exit(void);

int                 builtins(t_params *params, t_env **env, int *status);
char				*find_data_in_env(t_env *env, char *needle, int serial_num);
void				write_str(char *str, int fd, int flag);
t_env				*copy_envp_to_struct(char **envp);
int					open_fd(char *in, char *redir);
int 				parser(char **line, t_params **params, t_env *env, int *status);
int 				number_of_redirect(char *redir);
int					getcharacter(int fd, char **line);
//int 				error_handling(char *error, int status);
int 				check_redir(char **line);
char				*remove_spaces(char *line);
//int					reopen_fd(char **line, t_env *env, int *fd, int *status);
int					redirect_and_name_fd(char **line, t_env *env, int *fd, int *status);
void 				ft_lstadd_back_env(t_env **env, t_env *new);
char 				*return_token(char **line, t_env *env, int *status);
char				*handling_tokens_with_quotes(char **line, t_env *env, int *status);

int 				open_and_close_fd(char **line, t_params **params, t_env *env, int *status);

char				*expand_env_arg(char **line, t_env *env, int *status);
char				*append_to_array(char *src, char symb);
int 				check_unexpected_token(char **name_fd);


t_params 			*new_params_element(void);
t_env				*ft_lstnew_env(void *name, void *value);


void	 			init_params(t_params **params);
void				init_data(t_d *data);


void 				params_free(t_params **params, void (*del)(t_params *));
void 				env_free(t_env **env, void (*del)(t_env *));


void 				free_data(t_d *data);
void				free_params(t_params *params);
void				free_string(char **str);
void 				free_env(t_env **env);


void				del_list_content(void *content);
void				del_params_content(t_params *params);
void 				del_env_content(t_env *env);

#endif
