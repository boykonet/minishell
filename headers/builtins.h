/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 09:32:17 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/08 09:32:17 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libs/libft/libft.h"
# include "minishell.h"

int					ft_cd(t_list *args, t_env **env);
int					ft_pwd();
int					ft_echo(t_list *args);
int					ft_env(t_env **env, t_params *argv);
int					ft_export(t_env **env, t_params *argv);
int					ft_unset(t_env **env, t_params *argv);
int					ft_exit(t_list *args, int *error_status);

int					pipes_and_one_cmd(t_d **data, t_params *par, int *status);
int					pipes(t_d **data, t_params **params);
int					parent_pipes(t_pipes *pp);
void				fork_child_proc(t_d **data, t_params *par, t_pipes *pp);

char				*find_path(char *old_cmd, char *path, int *status);
int					builtins(t_d **data, t_params *params);
int					create_process(t_d **data, t_params *par, char **args, \
					char **envp);
void				handle_sig(int signo);
int					print_notification(t_params *argv, t_list *smth);
void				err_exit(char *str, int status);
char				*name_cmd(t_d **data, t_params *par, int *status);
void				execve_error(char *cmd, int *status);
void				change_pwd(t_env **env, char *str);
int					arg_for_cd(t_list *args, t_env **env, char **res);

#endif
