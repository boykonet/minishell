/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 03:32:28 by gkarina           #+#    #+#             */
/*   Updated: 2021/02/18 03:32:28 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXIC_H
# define LEXIC_H

int				lexic(char *line);
int				lexic_token(char **line, int ident);
int				spec_symb(int quotes, int escaping, int ident, char c);
int				check_unexpected_token(char *token);

#endif
