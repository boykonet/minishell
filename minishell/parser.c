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
	if (!ft_strncmp(str, "|", 1))
		return (1);
	else if (!ft_strncmp(str, ";", 1))
		return (2);
	return (0);
}

char		*remove_spaces(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}

char			*read_tokens(char *line)
{
	char			buff[2];
	char			*result;
	char			*tmp;
	int				flag;
	int				count;

	result = ft_strdup("");
	buff[1] = '\0';
	flag = 0;
	count = 0;
	if (line[count] != ' ')
	{
		if (line[count] == '\'' || line[count] == '\"')
		{
			flag = line[count] == '\'' ? 1 : 2;
			count++;
			while ((line[count] != '\'' && flag == 1) || (line[count] != '\"' && flag == 2))
				count++;
			if (line[count + 1])
			if (!(result = ft_substr(line, 0, ++count)))
				return (NULL);
			line += ft_strlen(result) + 1;
		}
		else
		{
			while (line[count] != ' ')
				count++;
			if (!(result = ft_substr(line, 0, count)))
				return (NULL);
			line++;
		}
	}
	return (result);
}

int			parser(t_params *params, char *line)
{
	t_list	*head;
	t_list	*curr;

	line = remove_spaces(line);
	if (!(head = ft_lstnew(read_tokens(line))))
		return (0);
	line += ft_strlen(head->content) + 1;
	curr = head;
	while (*line)
	{
		line = remove_spaces(line);
		if (!(curr->next = ft_lstnew(read_tokens(line))))
		{
			ft_lstclear(&head, &del_content);
			return (0);
		}
		curr = curr->next;
		line += ft_strlen(curr->content) + 1;
	}
	/* write(1, "<", 1); */
	/* write(1, line, 1); */
	/* write(1, ">", 1); */
	/* write(1, "\n", 1); */
	return (1);
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

void		write_params_in_struct(char **param, char *var)
{
	if (!(*param = ft_strdup(var)))
		return ();
}

int			main()
{
	char	*line;
	char	*curr;
	t_list	*list;
	t_list	*curr_list;
	int		i;
	t_params	params;

	i = 0;
	/* init_params(&params); */
	line = ft_strdup("    echo -n \'   \"qwerty\" qwerty qwerty   \' >> file.txt | grep -lE \"main\"");
	if (!(list = parser(line)))
		return (-1);
	while (list)
	{
		if (!ft_strncmp(list->content, "-", 1))
		if (!(params->command = ft_strdup(list->content)))
			return (NULL);
		list = list->next;
		if (*list->content == '-')
		{
			curr_list = list;
			while (*list->content == '-')
			{

			}
			curr = list->content;
			i = ft_strlen(list->content);
			if (!(params->flags = malloc(sizeof(char*) * i)))
				return (NULL);
			params->flags[i - 1] = NULL;
			i = 0;
			while (*curr)
			{
				if (!(params->flags = malloc(sizeof(char) * )
			}
		}
		list = list->next;
	}
	/* while (list) */
	/* { */
	/* 	printf("[%d] <%s>\n", i, list->content); */
	/* 	list = list->next; */
	/* 	i++; */
	/* } */
	/* printf("end\n"); */
	return (0);
}
