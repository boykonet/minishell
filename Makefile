NAME = minishell

MINISRCS = 	        srcs/expand_env_arg.c \
                    srcs/builtins.c \
                    srcs/copy_envp_to_struct.c \
                    srcs/del_content.c \
                    srcs/find_data_in_env.c \
                    srcs/free_params_in_struct.c \
                    srcs/ft_cd.c \
                    srcs/ft_exit.c \
                    srcs/ft_echo.c \
                    srcs/create_new_elements.c \
                    srcs/ft_pwd.c \
                    srcs/init.c \
                    srcs/redirects.c \
                    srcs/del_content.c \
                    srcs/getcharacter.c \
                    srcs/ft_cd.c \
                    srcs/ft_lstadd_back_env.c \
                    srcs/pipes.c \
                    srcs/find_path.c \
                    srcs/convert_from_to.c \
                    srcs/number_of_lines.c \
                    srcs/handling_tokens_with_quotes.c \
                    srcs/return_token.c \
                    srcs/append_to_array.c \
                    srcs/functions.c \
                    srcs/check_redir.c \
                    parser/parser.c \
                    parser/open_and_close_fd.c \
                    parser/open_fd.c

CFLAGS = -Wall -Wextra -Werror

SRCS =  ./other/main.c $(MINISRCS)

MINIOBJS = $(MINISRCS:%.c=%.o)

OBJS = $(SRCS:%.c=%.o)

INCLUDES = ./minishell.h \
		   ./libft/libft.h \
		   ./printf/libftprintf.h

CC = gcc

all: $(NAME)

$(NAME): $(OBJS) libft.a libftprintf.a libminishell.a $(INCLUDES)
	$(CC) $(CFLAGS) -L. -lft -lftprintf -lminishell -o $@ ./other/main.c

libft.a:
	$(MAKE) bonus -C ./libft CC=$(CC)
	mv ./libft/libft.a .

libftprintf.a:
	$(MAKE) all -C ./printf CC=$(CC)
	mv ./printf/libftprintf.a .

libminishell.a: $(MINIOBJS)
	ar rcs $@ $^
	ranlib $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./printf
	rm -rf $(OBJS)

fclean:
	$(MAKE) fclean -C ./printf
	$(MAKE) fclean -C ./libft
	rm -rf $(OBJS)
	rm -rf $(NAME) libft.a libftprintf.a libminishell.a

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re