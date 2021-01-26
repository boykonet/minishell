#ifndef BUILTINS_H
# define BUILTINS_H



int					ft_cd(t_list *args, t_env **env);
int					ft_pwd(char **pwd);
int					ft_echo(t_list *args, int fd);
int                 ft_exit(void);

#endif