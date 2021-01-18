# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/18 16:59:26 by gkarina           #+#    #+#              #
#    Updated: 2020/06/18 16:59:26 by gkarina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror

SRCS = ./src/ft_printf.c \
	   ./src/ft_itoa_base.c \
	   ./src/checker_printf.c \
	   ./src/dist_printf.c \
	   ./src/dist_char.c \
	   ./src/dist_string.c \
	   ./src/dist_p_i_d_u_x_x_big.c \
	   ./src/fill_array.c \
	   ./src/fill_spec.c \
	   ./src/fill_c_p_i_d_u_x_x_big_prc.c \
	   ./src/printf_spec.c \
	   ./src/printf_c.c \
	   ./src/printf_s.c \
	   ./src/printf_p.c \
	   ./src/printf_d_and_i.c \
	   ./src/printf_u.c \
	   ./src/printf_x_and_x_big.c \
	   ./src/printf_percent.c \

OBJS = $(SRCS:%.c=%.o)

INCLUDES = ./

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	cp ./libft/libft.a .
	mv libft.a $(NAME)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) -I$(INCLUDES) -o $@ $<

clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean:
	make fclean -C ./libft
	rm -f $(OBJS)
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
