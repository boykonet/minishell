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
//
//void		wait_line(char *str)
//{
////	char	*curr_location;
////	int		i;
//
//	/* i = 0; */
//	/* while (i < 2) */
//	/* { */
//
//	/* } */
////	write(1, curr_location, ft_strlen(curr_location));
//	write(1, str, ft_strlen(str));
//}

int				main(int argc, char **argv, char **envp)
{
	t_env		*env;
	t_params	*params;
	t_params	*d_p;
	t_list		*list;
	static int	status;
	char		*line;
	char 		*curr_symb;

	status = 0;
	if (!(env = copy_envp_to_struct(envp)))
		return (-1);
	while (TRUE)
	{
		line = NULL;
//		wait_line("minishell$ ");
		write(1, "minishell$ ", ft_strlen("minishell$ "));
		if ((getcharacter(0, &line)) < 0)
			return (-1);
		curr_symb = line;
		while (*curr_symb)
		{
			params = NULL;
			status = lexer(&curr_symb, &params, env);
			if (status > 0)
				break ;
			if (*curr_symb == ';')
				curr_symb++;
			d_p = params;
			while (d_p)
			{
				printf("%s\n", d_p->cmd);
				list = d_p->args;
				while (list)
				{
					printf("%s\n", list->content);
					list = list->next;
				}
				d_p = d_p->next;
			}
//			printf("\nvishel\n\n");
//			curr = tokens;
//				builtins(&params, ch, &status);
			params_free(&params, free_params);
		}
		free(line);
	}
	return (status);
	//     echo -n '<   "qwerty"   >'     4qwerty4     '<   qwerty   >''<   "qwerty"   >'    4qwerty4    '<   qwerty   >' >> file.txt | grep -lE "main"
}
