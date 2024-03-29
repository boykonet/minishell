/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 03:31:58 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 03:31:58 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVALUATOR_H
# define EVALUATOR_H

# include "minishell.h"

void		evaluator(t_d **data, t_params **par, int *status);
void		check_lists(t_params *params, t_eval *eval);
char		*expand_env_arg(char **line, t_eval *eval);
char		*handling_tokens_with_quotes(char **line, t_eval *eval);
char		*return_token(char **line, t_eval *eval);
char		*shape_name_fd(char *name, t_eval *eval);
int			number_of_redirect(char *redir);
void		open_and_close_fd(char *redir, char *name, t_eval *eval, \
			t_params **params);
int			open_fd(char *file, char *redir);

#endif
