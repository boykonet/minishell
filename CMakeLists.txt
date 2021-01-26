cmake_minimum_required(VERSION 3.15)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(gnl)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L. -lft -lftprintf")

add_executable(minishell
#        gnl/get_next_line.c
#        gnl/get_next_line.h
#        gnl/get_next_line_utils.c
        minishell/expand_env_arg.c
        minishell/open_fd.c
        minishell/builtins.c
        minishell/copy_envp_to_struct.c
        minishell/del_content.c
        minishell/find_data_in_env.c
        minishell/free_params_in_struct.c
        minishell/ft_cd.c
        minishell/ft_exit.c
        minishell/ft_echo.c
        minishell/create_new_elements.c
        minishell/ft_pwd.c
        minishell/init.c
        minishell/open_and_close_fd.c
        minishell/main.c
#        minishell/meta.c
        minishell/parser.c
        minishell/redirects.c
#        minishell/write_str.c
        minishell/del_content.c
        minishell/getcharacter.c
        minishell/ft_cd.c
        minishell/ft_lstadd_back_env.c

        minishell/handling_tokens_with_quotes.c
        minishell/return_token.c
        minishell/append_to_array.c
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
