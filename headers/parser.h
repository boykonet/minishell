/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 09:32:44 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/08 09:32:44 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

char				*append_to_array(char *src, char symb);
char				*expand_env_arg(char **line, t_eval *eval);
char				*handling_tokens_with_quotes(char **line, t_eval *eval);
void				open_and_close_fd(char *redir, char *name, t_eval *eval, t_params **params);
int					open_fd(char *in, char *redir);
t_params			*parser(char *line);
int					number_of_redirect(char *redir);
char				*return_token(char **line, t_eval *eval);
void				redirect_and_name_fd(char *redir, char *name, t_eval *eval, int *fd);
int					check_unexpected_token(char *token);
char				*shape_name_fd(char *name, t_eval *eval);
char 				*simple_token(char **line);

#endif
