/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkarina <gkarina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 00:11:07 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/21 00:11:07 by gkarina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			check_tokens(char *str)
{
	if (!ft_strncmp(str, "|"))
		return (1);
	else if (!ft_strncmp(str, ";"))
		return (2);
	return (0);
}

int			remove_spaces(char *line)
{
	while (*line == ' ')
	{
		/* if (!check_tokens(*line) */
		/* 	return (0); */
		line++;
	}
	return (1);
}

char		*write_in_string(char **line, int signal)
{
	char	*str;
	
	while (ft_isalpha(**line))
	{
		
	}
	return (str);
}

int			read_command(char **command, char **line)
{
	if (!remove_spaces(line))
		return (2);
	while (*line)
	{
		
	}
	return (1);
}

char		*read_tokens(char *line)
{
	char	buff[2];
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	ft_memset(buff, '\0', sizeof(char) * 2);
	while (*line != ' ')
	{
		buff[0] = *line;
		tmp = result;
		if (!(result = ft_strjoin(result, buff)))
			return (NULL);
		free(tmp);
		tmp = NULL;
		line++;
	}
	return (result);
}

t_list		*parser(/*t_params *params, */char **line)
{
	t_list	*head;
	t_list	*curr;
	char	*line_curr;

	line_curr = (*line);
	curr = head;
	while (*line_curr)
	{
		remove_spaces(&line_curr);
		if (!(curr = ft_lstnew(NULL)))
		{
			/* ft_lstclear(&head, &del_content); */
			return (NULL); // 0
		}
		curr->content = read_tokens(line_curr);
		printf("%s\n\n", curr->content);
		line_curr += ft_strlen(curr->content) + 1;
		printf("%s\n", line_curr);
//		if (*line_curr == '\0')
//			break ;
		curr = curr->next;
	}
	return (head);
	/* char	buff[2]; */
	/* char	*tmp; */
	/* int		count_args; */

	/* i = 0; */
	/* count_args = 0; */
	/* buff[1] = '\0'; */
	/* while (*line) */
	/* { */
	/* 	read_command(&params->command, line); */
	/* 	read_flags(line); */
	/* 	read_arguments(line); */
	/* 	read_resirect(line); */
	/* 	read_name_fd(line); */
	/* 	while (ft_isalpha(*line) && check_tokens(*line)) */
	/* 	{ */
	/* 		if (!params->command) */
	/* 			params->command = ft_strdup(""); */
	/* 		buff[0] = *line; */
	/* 		tmp = params->command; */
	/* 		params->command = ft_strjoin(params->command, buff); */
	/* 		free(tmp); */
	/* 		tmp = NULL; */
	/* 		line++; */
	/* 	} */
	/* 	else if (*line == '-') */
	/* 	{ */
	/* 		line++; */
	/* 		if (!params->flags) */
	/* 			params->flags = ft_strdup(""); */
	/* 		while (ft_isalpha(*line) && check_tokens(*line)) */
	/* 		{ */
	/* 			buff[0] = *line; */
	/* 			tmp = params->flags; */
	/* 			params->flags = ft_strjoin(params->flags, buff); */
	/* 			free(tmp); */
	/* 			tmp = NULL; */
	/* 			line++; */
	/* 		} */
	/* 		if (!check_tokens(*line)) */
	/* 			return (-1); */
	/* 	} */
	/* 	else if (*line == '$') */
	/* 	{ */
	/* 		while (ft_isalnum(*line) || *line == '=' || *line == '$') */
	/* 		{ */
	/* 			buff[0] = *line; */
	/* 			tmp = params->args[count_args]; */
	/* 			params->args[count_args] = ft_strjoin(params->args[count_args], buff); */
	/* 			free(tmp); */
	/* 			tmp = NULL; */
	/* 			line++; */
	/* 		} */
	/* 		count_args++; */
	/* 	} */
	/* 	line++; */
	/* } */
	/* if (*line == '|') */
	/* 	return (2); */
	/* else if (*line == ';') */
	/* 	return (1); */
	/* return (0); */
}

int			main()
{
	char	*line;
	t_list	*list;

	line = ft_strdup("echo -n qwerty qwerty qwerty >> file.txt | grep -lE \"main\"");
	list = parser(&line);
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
	return (0);
}
