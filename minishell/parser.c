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
	char 			*dupl_line;
	char			*tmp;
	int				flag;
	int				count;
	char 			*result1;

	result1 = ft_strdup("");
	buff[1] = '\0';
	flag = 0;
	count = 0;
	dupl_line = line;
	while (*dupl_line != ' ')
	{
		if (*dupl_line == '\'' || *dupl_line == '\"')
		{
			if (*dupl_line == '\'')
				flag = 1;
			else
				flag = 2;
			dupl_line++;
			while ((*dupl_line != '\'' && flag == 1) || (*dupl_line != '\"' && flag == 2))
				dupl_line++;
			if (!(result = ft_substr(line, 0, ++dupl_line - line)))
				return (NULL);
		}
		else
		{
			while (*dupl_line != ' ')
				dupl_line++;
			if (!(result = ft_substr(line, 0, dupl_line - line)))
				return (NULL);
		}
		line += ft_strlen(result);
		tmp = result1;
		result1 = ft_strjoin(result1, result);
		free(tmp);
		free(result);
	}
	return (result1);
}

t_list		*parser(t_params *params, char *line)
{
	t_list	*head;
	t_list	*curr;

	line = remove_spaces(line);
	if (!(head = ft_lstnew(read_tokens(line))))
		return (0);
	line += ft_strlen(head->content);
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
		line += ft_strlen(curr->content);
	}
	return (head);
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
	init_params(&params);
	line = ft_strdup("    echo -n \'<   \"qwerty\"   >\'     4qwerty4     \'<   qwerty   >\'\'<   \"qwerty\"   >\'    4qwerty4    \'<   qwerty   >\' >> file.txt | grep -lE \"main\"");
	if (!(list = parser(&params, line)))
		return (-1);
	while (list)
	{
		if (!command)
			params->command = ft_strdup(list->content);
		else
		{
			
			i++;
		}
		list = list->next;
	}
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
		i++;
	}
	printf("end\n");
	return (0);
}
