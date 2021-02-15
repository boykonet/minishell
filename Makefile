NAME = minishell

MINISRCS =	builtins/builtins.c \
			builtins/create_process.c \
			builtins/find_path.c \
			builtins/ft_cd.c \
            builtins/ft_echo.c \
            builtins/ft_env.c \
            builtins/ft_exit.c \
            builtins/ft_export.c \
            builtins/ft_pwd.c \
            builtins/ft_unset.c \
            builtins/pipes.c \
            builtins/pipes_and_one_cmd.c \
            builtins/print_notification.c \
            builtins/signals.c \
            evaluator/evaluator.c \
            lexic/lexic.c \
            other/check_command.c \
            other/check_word.c \
            other/convert_from_to.c \
			other/copy_envp_to_struct.c \
			other/create_new_elements.c \
			other/del_content.c \
			other/find_in_env.c \
            other/free_params_in_struct.c \
            other/ft_lstadd_back_env.c \
            other/ft_lstsize_env.c \
            other/ft_split_by.c \
            other/ft_strcmp.c \
			other/functions.c \
			other/getcharacter.c \
			other/init.c \
			other/lst_func.c \
			other/params_del.c \
			other/prompt_line.c \
			other/sort.c \
			parser/append_to_array.c \
            parser/check_unexpected_token.c \
            parser/expand_env_arg.c \
            parser/handling_tokens_with_quotes.c \
            parser/open_and_close_fd.c \
            parser/open_fd.c \
            parser/parser.c \
			parser/number_of_redirect.c \
			parser/return_token.c \
			parser/shape_name_fd.c

CFLAGS = -fsanitize=address -fno-omit-frame-pointer -g -Wall -Wextra -Werror

SRCS =  ./other/main.c $(MINISRCS)

MINIOBJS = $(MINISRCS:%.c=%.o)

OBJS = $(SRCS:%.c=%.o)

HEADERS =	./headers/minishell.h \
			./headers/builtins.h \
			./headers/other.h \
			./headers/parser.h \
			./libs/libft/libft.h

INCLUDEDIR = ./headers

CC = clang

all: $(NAME)

$(NAME): $(OBJS) libft.a libminishell.a $(HEADERS)
	$(CC) $(CFLAGS) -L. -I $(INCLUDEDIR) -o $@ ./other/main.c -lminishell -lft

libft.a:
	$(MAKE) bonus -C ./libs/libft CC=$(CC)
	mv ./libs/libft/libft.a .

libminishell.a: $(MINIOBJS)
	ar rcs $@ $^
	ranlib $@

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDEDIR) -c $< -o $@

clean:
	$(MAKE) clean -C ./libs/libft
	rm -rf $(OBJS)

fclean:
	$(MAKE) fclean -C ./libs/libft
	rm -rf $(OBJS)
	rm -rf $(NAME) libft.a libminishell.a

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
