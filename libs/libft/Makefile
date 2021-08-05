# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/08 17:20:03 by gkarina           #+#    #+#              #
#    Updated: 2020/05/08 17:20:03 by gkarina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

SRCS =			./srcs/ft_memset.c \
				./srcs/ft_bzero.c \
				./srcs/ft_memcpy.c \
				./srcs/ft_memccpy.c \
				./srcs/ft_memmove.c \
				./srcs/ft_memchr.c \
				./srcs/ft_memcmp.c \
				./srcs/ft_strlen.c \
				./srcs/ft_strlcpy.c \
				./srcs/ft_strlcat.c \
				./srcs/ft_strchr.c \
				./srcs/ft_strrchr.c \
				./srcs/ft_strnstr.c \
				./srcs/ft_strncmp.c \
				./srcs/ft_atoi.c \
				./srcs/ft_isalpha.c \
				./srcs/ft_isdigit.c \
				./srcs/ft_isalnum.c \
				./srcs/ft_isascii.c \
				./srcs/ft_isprint.c \
				./srcs/ft_toupper.c \
				./srcs/ft_tolower.c \
				./srcs/ft_calloc.c \
				./srcs/ft_strdup.c \
				./srcs/ft_substr.c \
				./srcs/ft_strjoin.c \
				./srcs/ft_strtrim.c \
				./srcs/ft_split.c \
				./srcs/ft_itoa.c \
				./srcs/ft_strmapi.c \
				./srcs/ft_putchar_fd.c \
				./srcs/ft_putstr_fd.c \
				./srcs/ft_putendl_fd.c \
				./srcs/ft_putnbr_fd.c

SRCS_BONUS =	./srcs/ft_lstnew.c \
				./srcs/ft_lstadd_front.c \
				./srcs/ft_lstsize.c \
				./srcs/ft_lstlast.c \
				./srcs/ft_lstadd_back.c \
				./srcs/ft_lstdelone.c \
				./srcs/ft_lstclear.c \
				./srcs/ft_lstiter.c \
				./srcs/ft_lstmap.c

OBJS = $(SRCS:%.c=%.o)

OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)

ifdef WITH_BONUS
PROG_OBJS = $(OBJS) $(OBJS_BONUS)
else
PROG_OBJS = $(OBJS)
endif

INCLUDEDIR = ./

CFLAGS = -Wall -Wextra -Werror -I $(INCLUDEDIR)

all: $(NAME)

$(NAME): $(PROG_OBJS)
	ar rc $(NAME) $(PROG_OBJS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

bonus:
	$(MAKE) WITH_BONUS=1 all

.PHONY: all clean fclean re bonus
