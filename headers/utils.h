/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 21:53:26 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 21:53:26 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "../libs/libft/libft.h"

char				**convert_struct_to_array(t_list *lst);
char				**convert_env_to_arr(t_env *env);
t_env				*copy_envp_to_struct(char **envp);

t_params			*new_params_element(void);
t_env				*ft_lstnew_env(void *name, void *value);
t_env				*new_item(t_list *item);
int					ft_lstsize_env(t_env *lst);
int					ft_lstsize_params(t_params *par);
void				ft_lstadd_back_env(t_env **env, t_env *new);

void				del_list_content(void *content);
void				del_params_content(t_params *params);
void				del_env_content(t_env *env);
void				del_data_content(t_d *data);
void				lst_delete(t_list **head, t_list *d);
void				lst_replase(t_list **head, t_list **list, t_list *d);
t_params			*split_par(t_params **head, int len);

char				*find_data_in_env(t_env *env, char *needle, int serial_num);
t_env				*find_list_env(t_env *env, char *needle, int spec);

void				params_free(t_params **params, void (*del)(t_params *));
void				env_free(t_env **env, void (*del)(t_env *));
void				free_string(char **str);
void				free_env_element(t_env *lst);
void				params_delete(t_params **head, t_params *d);

void				add_params_env(t_env **curr, char *name, char *value);
char				*remove_spaces(char *line);
char				**copy_array(char **src);
char				*append_to_array(char *src, char symb);
void				quicksort(char **arr, int low, int high);
void				close_fd(int fd);
int					count_params(t_params *head);
size_t				number_of_lines(char **arr);
int					getcharacter(int fd, char **line);

void				init_params(t_params **params);
void				init_pipes(t_pipes *pp);
void				init_data(t_d **data);
void				init_eval(t_d **data, t_eval *eval, const int *status);

int					check_command(char *cmd);
int					check_word(t_list *str);
int					ft_strcmp(const char *s1, const char *s2);
void				*ft_split_by_quation(char *str, t_env *lst, char c);

void				print_prompt_line(t_d *data, int signo);
void				logname_folder_home(t_env *env, char **logname, \
					char **folder, char **home);

#endif
