/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:15:41 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/19 16:15:41 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t		number_of_lines(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

void		wait_line(char *str)
{
//	char	*curr_location;
//	int		i;

	/* i = 0; */
	/* while (i < 2) */
	/* { */

	/* } */
//	write(1, curr_location, ft_strlen(curr_location));
	write(1, str, ft_strlen(str));
}

int				main(int argc, char **argv, char **envp)
{
	t_env		*env;
//	t_list		*params;
//	t_list		*fd;
	t_list		*tokens;
	static int	status;
	char		*line;
	char 		*curr_symb;

	if (!(env = copy_envp_to_struct(envp)))
		return (-1);
	while (TRUE)
	{
		line = NULL;
		wait_line("minishell$ ");

		if ((getcharacter(0, &line)) < 0)
			return (-1);
		curr_symb = line;
		while (*curr_symb)
		{
			tokens = NULL;

			tokens = lexer(&curr_symb, env);
			if (*curr_symb == ';')
				curr_symb++;
			while (tokens)
			{
				printf("%s\n", tokens->content);
				tokens = tokens->next;
			}
			printf("\nvishel\n\n");
//			curr = tokens;
//			while (curr)
//			{
//				init_params(&params);
//				init_fd(&fd);
//			parser(&tokens, params, fd, &status);
//				builtins(&params, ch, &status);
//			ft_lstclear(&params, &free_params);
//			ft_lstclear(&fd, &free_fd);
//			free_params(&params);
//			free_fd(&fd);
//			}
			ft_lstclear(&tokens, del_content);
		}
		free(line);
	}
	return (status);
	//     echo -n '<   "qwerty"   >'     4qwerty4     '<   qwerty   >''<   "qwerty"   >'    4qwerty4    '<   qwerty   >' >> file.txt | grep -lE "main"
}
