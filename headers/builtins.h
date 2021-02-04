#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libs/libft/libft.h"
# include "minishell.h"

int					ft_cd(t_list *args, t_env **env, int fd);
int					ft_pwd(char **pwd);
int					ft_echo(t_list *args, int fd);
int					ft_env(t_env **env, t_params *argv);
int					ft_export(t_env **env, t_params *argv);
int					ft_unset(t_env **env, t_params *argv);
int                 ft_exit(t_list *args, int *error_status);

int					pipes(t_d **data);
char				*find_path(char *old_cmd, char *path);
int					builtins(t_d **data, t_params *params);
int					create_process(char **args, char **envp, char *cmd, int in, int out);

#endif