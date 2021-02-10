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

char				*append_to_array(char *src, char symb);
int					check_redir(char **line);
char				*expand_env_arg(char **line, t_parser *p);
char				*handling_tokens_with_quotes(char **line, t_parser *p);
int					open_and_close_fd(char **line, t_parser *p, \
					t_params **params);
int					open_fd(char *in, char *redir);
void				parser(char **line, t_d **data, int *status);
int					number_of_redirect(char *redir);
char				*return_token(char **line, t_parser *p);
int					redirect_and_name_fd(char **line, t_parser *p, int *fd);
int					check_unexpected_token(char **name_fd);
char				*shape_name_fd(char **line, char *curr, t_parser *p);

#endif
