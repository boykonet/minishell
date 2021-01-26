NAME = minishell

MINISRCS = 	        minishell/expand_env_arg.c \
                    minishell/open_fd.c \
                    minishell/builtins.c \
                    minishell/copy_envp_to_struct.c \
                    minishell/del_content.c \
                    minishell/find_data_in_env.c \
                    minishell/free_params_in_struct.c \
                    minishell/ft_cd.c \
                    minishell/ft_exit.c \
                    minishell/ft_echo.c \
                    minishell/create_new_elements.c \
                    minishell/ft_pwd.c \
                    minishell/init.c \
                    minishell/open_and_close_fd.c \
                    minishell/parser.c \
                    minishell/redirects.c \
                    minishell/del_content.c \
                    minishell/getcharacter.c \
                    minishell/ft_cd.c \
                    minishell/ft_lstadd_back_env.c \
                    minishell/pipes.c \
                    minishell/find_path.c \
                    minishell/convert_from_to.c \
                    minishell/number_of_lines.c \
                    minishell/handling_tokens_with_quotes.c \
                    minishell/return_token.c \
                    minishell/append_to_array.c

CFLAGS = -Wall -Wextra -Werror

SRCS =  ./minishell/main.c $(MINISRCS)

MINIOBJS = $(MINISRCS:%.c=%.o)

OBJS = $(SRCS:%.c=%.o)

INCLUDES = ./minishell.h \
		   ./libft/libft.h
		   ./printf/libftprintf.h

CC = gcc

all: $(NAME)

$(NAME): $(OBJS) libft.a libftprintf.a $(INCLUDES)
	$(CC) $(CFLAGS) -L. -lft -lftprintf -o $@ ./minishell/main.c

libft.a:
	$(MAKE) bonus -C ./libft CC=$(CC)
	mv ./libft/libft.a .

libftprintf.a:
	$(MAKE) all -C ./printf CC=$(CC)
	mv ./printf/libftprintf.a .

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./printf
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) libft.a libftprintf.a

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re