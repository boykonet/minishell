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
	t_list			*args;
	char			*flags;
	char			*command;
	char			*redir;
	char			*name_fd;
	char			*error;
}					t_params;

int					ft_cd(char *args, char **home, char **pwd_curr, char **old_pwd);
void				builtins(t_params *params, char **home, char **pwd_curr, char **old_pwd);
void				del_content(void *content);
void				find_data_in_env(t_env *env, char *needle, char **result, int serial_num);
char				*ft_pwd(char *pwd);
int					init_fd(char *name_fd, char *redir);
void				init_params(t_params *params);
t_list				*parser(t_params *params, char *line);
void				write_str(char *str, int fd, int flag);
t_env				*ft_lstnew_env(void *name, void *value);
t_env				*copy_envp_to_struct(char **envp);

#endif
