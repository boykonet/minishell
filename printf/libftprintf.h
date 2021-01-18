/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:57:04 by gkarina           #+#    #+#             */
/*   Updated: 2020/06/18 14:57:04 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include "./libft/libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct	s_data
{
	char		*buff;
	char		*var;
	char		c;
	int			temp;
	int			sign;
	int			dot;
	int			size;
	int			count;
	int			width;
	int			prec;
	int			s_arr;
	int			n_num;
	int			err;
	int			flag_zero;
	int			flag_neg;
	int			without_flags;
}				t_data;

int				ft_printf(const char *fmt, ...);
char			*ft_itoa_base(long int num, size_t base);
int				printf_c(t_data *data, va_list ap, char *s);
int				printf_s(t_data *data, va_list ap, char *s);
int				printf_p(t_data *data, va_list ap, char *s);
int				printf_d_and_i(t_data *data, va_list ap, char *s);
int				printf_u(t_data *data, va_list ap, char *s);
int				printf_x_and_x_big(t_data *data, va_list ap, char *s);
int				printf_percent(t_data *data, va_list ap, char *s);
int				checker_printf(t_data *data, va_list ap);
int				dist_printf(t_data *data);
int				dist_char(t_data *data);
int				dist_string(t_data *data, int len_str);
int				dist_p_i_d_u_x_x_big(t_data *data, char ch, int len_str,
				int diff_num);
void			fill_array(t_data *data, char *str, int len_str,
				int differ_num);
void			fill_spec(t_data *data, char *str, int len_str, int diff_num);
void			fill_c_p_i_d_u_x_x_big_prc(t_data *data, char *str, int len_str,
				int diff_num);
int				printf_spec(t_data *data, va_list ap, char ch,
				int (*f)(t_data*, va_list));

#endif
