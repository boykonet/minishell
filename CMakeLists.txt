cmake_minimum_required(VERSION 3.15)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(gnl)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I ../headers -L. -lft -lftprintf")

add_executable(srcs
#        gnl/get_next_line.c
#        gnl/get_next_line.h
#        gnl/get_next_line_utils.c
        builtins/builtins.c
        builtins/find_path.c
		builtins/ft_cd.c
		builtins/ft_echo.c
		builtins/ft_exit.c
		builtins/ft_pwd.c
		builtins/pipes.c
		other/convert_from_to.c
		other/copy_envp_to_struct.c
		other/create_new_elements.c
		other/del_content.c
		other/find_data_in_env.c
		other/free_params_in_struct.c
		other/ft_lstadd_back_env.c
		other/functions.c
		other/getcharacter.c
		other/init.c
		other/main.c
		parser/append_to_array.c
		parser/check_redir.c
		parser/expand_env_arg.c
		parser/handling_tokens_with_quotes.c
		parser/open_and_close_fd.c
		parser/open_fd.c
		parser/parser.c
		parser/number_of_redirect.c
		parser/return_token.c
        headers/minishell.h

        )
