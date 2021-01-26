cmake_minimum_required(VERSION 3.15)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(gnl)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L. -lft -lftprintf")

add_executable(srcs
#        gnl/get_next_line.c
#        gnl/get_next_line.h
#        gnl/get_next_line_utils.c
        srcs/expand_env_arg.c
        srcs/open_fd.c
        srcs/builtins.c
        srcs/copy_envp_to_struct.c
        srcs/del_content.c
        srcs/find_data_in_env.c
        srcs/free_params_in_struct.c
        srcs/ft_cd.c
        srcs/ft_exit.c
        srcs/ft_echo.c
        srcs/create_new_elements.c
        srcs/ft_pwd.c
        srcs/init.c
        srcs/open_and_close_fd.c
        srcs/main.c
        srcs/parser.c
        srcs/redirects.c
        srcs/del_content.c
        srcs/getcharacter.c
        srcs/ft_cd.c
        srcs/ft_lstadd_back_env.c
        srcs/pipes.c
        srcs/find_path.c
        srcs/convert_from_to.c
        srcs/number_of_lines.c

        srcs/handling_tokens_with_quotes.c
        srcs/return_token.c
        srcs/append_to_array.c
        minishell.h
        libft/ft_strncmp.c
        libft/ft_strtrim.c
        libft/ft_strjoin.c
        libft/ft_strdup.c
        libft/ft_strchr.c
        libft/ft_strdup.c
        libft/ft_lstclear.c
        libft/ft_lstnew.c
        libft/ft_memset.c
        libft/ft_strrchr.c
        libft/ft_strlcpy.c
        libft/ft_strlen.c
        libft/ft_strtrim.c
        libft/ft_strjoin.c
        libft/ft_substr.c
        libft/ft_calloc.c
        libft/ft_isalnum.c
        libft/ft_lstdelone.c
        libft/ft_itoa.c
        )
