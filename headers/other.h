#ifndef OTHER_H
# define OTHER_H

# include "minishell.h"
# include "../libs/libft/libft.h"

t_list		        *convert_array_to_struct(char **array);
char	        	**convert_struct_to_array(t_list *lst);
t_env				*copy_envp_to_struct(char **envp);

t_params 			*new_params_element(void);
t_env				*ft_lstnew_env(void *name, void *value);

void				del_list_content(void *content);
void				del_params_content(t_params *params);
void 				del_env_content(t_env *env);

char				*find_data_in_env(t_env *env, char *needle, int serial_num);

void 				params_free(t_params **params, void (*del)(t_params *));
void 				env_free(t_env **env, void (*del)(t_env *));
void 				free_data(t_d *data);
void				free_string(char **str);

void 				ft_lstadd_back_env(t_env **env, t_env *new);
char				*remove_spaces(char *line);
char 				**copy_array(char **src);
size_t				number_of_lines(char **arr);
int					getcharacter(int fd, char **line);

void	 			init_params(t_params **params);
void				init_data(t_d *data);

#endif