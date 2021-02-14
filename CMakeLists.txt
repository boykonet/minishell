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
		builtins/ft_unset.c
		builtins/pipes.c
		builtins/pipes_and_one_cmd.c
		builtins/create_process.c
		builtins/signals.c
		builtins/print_notification.c
		other/convert_from_to.c
		other/copy_envp_to_struct.c
		other/create_new_elements.c
		other/del_content.c
		other/find_in_env.c
		other/free_params_in_struct.c
		other/ft_lstadd_back_env.c
		other/ft_lstsize_env.c
		other/functions.c
		other/getcharacter.c
		other/init.c
		other/main.c
		other/prompt_line.c
		parser/append_to_array.c
		parser/check_redir.c
		parser/expand_env_arg.c
		parser/handling_tokens_with_quotes.c
		parser/open_and_close_fd.c
		parser/open_fd.c
		parser/parser.c
		parser/number_of_redirect.c
		parser/return_token.c
		parser/check_unexpected_token.c
		parser/shape_name_fd.c
		other/sort.c
        headers/minishell.h
		evaluator/evaluator.c
		lexic/lexic.c
		other/check_word.c
		builtins/ft_env.c
		builtins/ft_export.c
		other/ft_split_by.c
		other/check_command.c
		other/ft_strcmp.c

        )
