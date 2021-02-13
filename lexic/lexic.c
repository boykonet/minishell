#include "minishell.h"
#include "other.h"
#include "parser.h"

int				check_redir_fd(char **line)
{
	char		*redir;
	char		*nfd;
	char		*curr;
	int 		i;

	curr = (*line);
	i = 0;
	if (check_redir(line) == -1)
//	while (i < 2 && *curr && *curr = *(curr + 1) && *curr != ' ')
//	{
//		curr++;
//		i++;
//	}
//	if (!(redir = ft_substr(*line, 0, curr - *line)))
//		exit(errno);
//	if (number_of_redirect(redir) == -1)
//
	curr = remove_spaces(curr);
	(*line) = curr;
	nfd = shape_name_fd(line, curr, p);
	if (!p->quotes)
		check_unexpected_token(nfd, p);
	if (p->exit_status != 2)
	{
		if ((*fd = open_fd(nfd, redir)) < 0)
		{
			p->status = 1;
			p->exit_status = 2;
		}
	}
	free(redir);
	free(nfd);
	if (p->status && p->exit_status == 2)
		return (0);
	return (1);
}

int 		lexic_token(char **line, t_lexic *lexic)
{
	char 	c;

	c = *(*line);
	while (c)
	{
		if (lexic->quotes == 0 && c == ' ')
			break ;
		else if (lexic->quotes == 0 && (c == ';' || c == '|'))
			return (1);
		else if (lexic->quotes == 0 && (c == '>' || c == '<'))
			return (2);
		else if (lexic->quotes == 0 && (c == ')' || c == '(' || c == '&'))
			return (3);
		if (c == '\\' && lexic->escaping == 0)
			lexic->escaping = 1;
		else if (c == '\\' && lexic->escaping == 1)
			lexic->escaping = 2;
		if ((c == '\'' || c == '\"') && lexic->escaping == 0 && lexic->quotes == 0)
			lexic->quotes = 1;
		else if ((c == '\'' || c == '\"') && lexic->escaping == 0 && lexic->quotes == 1)
			lexic->quotes = 2;
		if ((lexic->escaping == 1 && c != '\\') || lexic->escaping == 2)
			lexic->escaping = 0;
		if (lexic->quotes == 2)
			lexic->quotes = 0;
		(*line)++;
		c = *(*line);
	}
	return (0);
}

int 		lexic(char *line)
{
	t_lexic lexic;
	int 	r;

	lexic.status = 0;
	lexic.escaping = 0;
	lexic.quotes = 0;
	while (*line && !lexic.status)
	{
		line = remove_spaces(line);
		r = lexic_token(&line, &lexic);
		if (r == 1)
		{
			if (*line == *(line + 1))
				lexic.status = check_unexpected_token(line);
			else
				lexic.status = check_unexpected_token(line + 1);
		}
//		else if (r == 2)
//			lexic.status = check_redirects();
		else if (r == 3)
			lexic.status = check_unexpected_token(line);
	}
	return (lexic.status);
}