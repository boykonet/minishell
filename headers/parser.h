#ifndef PARSER_H
# define PARSER_H

//# include "./minishell.h"

char				*append_to_array(char *src, char symb);
int 				check_redir(char **line);
char				*expand_env_arg(char **line, t_env *env, int *status);
char				*handling_tokens_with_quotes(char **line, t_env *env, int *status);
int 				open_and_close_fd(char **line, t_params **params, t_env *env, int *status);
int					open_fd(char *in, char *redir);
int 				parser(char **line, t_params **params, t_env *env, int *status);
int 				number_of_redirect(char *redir);
char 				*return_token(char **line, t_env *env, int *status);
int					redirect_and_name_fd(char **line, t_env *env, int *fd, int *status);
int 				check_unexpected_token(char **name_fd);

#endif