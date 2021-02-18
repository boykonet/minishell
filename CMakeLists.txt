cmake_minimum_required(VERSION 3.15)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(gnl)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I ../headers -L. -lft -lftprintf")

add_executable(srcs
		builtins/arg_for_cd.c
builtins/builtins.c
builtins/child_parent.c
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
lexic/lexic_token.c
utils/append_to_array.c
utils/check_command.c
utils/check_word.c
utils/convert_from_to.c
utils/copy_envp_to_struct.c
utils/create_new_elements.c
utils/del_content.c
utils/find_in_env.c
utils/free_params_in_struct.c
utils/ft_lstadd_back_env.c
utils/ft_lstsize_env.c
utils/ft_split_by.c
utils/ft_strcmp.c
utils/functions.c
utils/getcharacter.c
utils/init.c
utils/lst_func.c
utils/params_del.c
utils/prompt_line.c
utils/sort.c
parser/parser.c
		utils/main.c

        )
