cmake_minimum_required(VERSION 3.15)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(gnl)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I ../headers -L. -lft -lftprintf")

add_executable(srcs
		builtins/arg_for_cd.c
		builtins/builtins.c
builtins/create_process.c
builtins/find_path.c
builtins/ft_cd.c
builtins/ft_echo.c
builtins/ft_env.c
builtins/ft_exit.c
builtins/ft_export.c
builtins/ft_pwd.c
builtins/ft_unset.c
builtins/pipes.c
builtins/pipes_and_one_cmd.c
builtins/print_notification.c
builtins/signals.c
		evaluator/check_lists.c
		builtins/child_parent.c
evaluator/evaluator.c
evaluator/expand_env_arg.c
evaluator/handling_tokens_with_quotes.c
evaluator/number_of_redirect.c
evaluator/open_and_close_fd.c
evaluator/open_fd.c
evaluator/return_token.c
evaluator/shape_name_fd.c
lexic/check_unexpected_token.c
lexic/lexic.c
other/append_to_array.c
other/check_command.c
other/check_word.c
other/convert_from_to.c
other/copy_envp_to_struct.c
other/create_new_elements.c
other/del_content.c
other/find_in_env.c
other/free_params_in_struct.c
other/ft_lstadd_back_env.c
other/ft_lstsize_env.c
other/ft_split_by.c
other/ft_strcmp.c
other/functions.c
other/getcharacter.c
other/init.c
other/lst_func.c
other/params_del.c
other/prompt_line.c
other/sort.c
parser/parser.c
		other/main.c

        )
