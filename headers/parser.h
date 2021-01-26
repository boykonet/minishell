#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "../minishell.h"

int 				parser(char **line, t_params **params, t_env *env, int *status);
int					open_fd(char *in, char *redir);
int 				number_of_redirect(char *redir);
int 				open_and_close_fd(char **line, t_params **params, t_env *env, int *status);
int					redirect_and_name_fd(char **line, t_env *env, int *fd, int *status);
char 				*return_token(char **line, t_env *env, int *status);
char				*append_to_array(char *src, char symb);


#endif