#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libs/libft/libft.h"
# include "minishell.h"

int					ft_cd(t_list *args, t_env **env);
int					ft_pwd(char **pwd);
int					ft_echo(t_list *args, int fd);
int                 ft_exit(void);

int					pipes(t_params *params, t_env **env, int *status);
char				*find_path(char *old_cmd, char *path);
int					builtins(t_params *params, t_env **env, int *status);

#endif