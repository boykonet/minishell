#include "minishell.h"
#include "other.h"
#include "parser.h"

int 		spec_symb(int quotes, int ident, char c)
{
	if (quotes == 0 && c == ' ')
		return (1);
	else if (quotes == 0 && (c == ';' || c == '|'))
		return (2);
	else if (!ident && quotes == 0 && (c == '>' || c == '<'))
		return (3);
	else if (!ident && quotes == 0 && (c == ')' || c == '(' || c == '&'))
		return (4);
	return (0);
}

int 		lexic_token(char **line, int ident)
{
	t_lexic lexic;
	int 	r;
	char 	c;

	lexic.escaping = 0;
	lexic.quotes = 0;
	c = *(*line);
	while (c)
	{
		if ((r = spec_symb(lexic.quotes, ident, c)))
			return (r);
		if (c == '\\' && lexic.escaping == 0)
			lexic.escaping = 1;
		else if (c == '\\' && lexic.escaping == 1)
			lexic.escaping = 2;
		if ((c == '\'' || c == '\"') && lexic.escaping == 0 && lexic.quotes == 0)
			lexic.quotes = 1;
		else if ((c == '\'' || c == '\"') && lexic.escaping == 0 && lexic.quotes == 1)
			lexic.quotes = 2;
		if ((lexic.escaping == 1 && c != '\\') || lexic.escaping == 2)
			lexic.escaping = 0;
		if (lexic.quotes == 2)
			lexic.quotes = 0;
		(*line)++;
		c = *(*line);
	}
	return (0);
}

int				check_redir_fd(char **line)
{
	char		*nfd;
	char		*curr;
	int 		status;
	int 		r;

	status = 0;
	nfd = NULL;
	if (!ft_strncmp(*line, ">>", 2))
		*line = *line + 2;
	else if (!ft_strncmp(*line, ">", 1) || !ft_strncmp(*line, "<", 1))
		*line = *line + 1;
	*line = remove_spaces(*line);
	curr = (*line);
	r = lexic_token(line, 0);
	nfd = ft_substr(curr, 0, *line - curr);
	if (*nfd == '\0' && (((*curr == ';' || *curr == '|') && r == 1) || \
	((*curr == '<' || *curr == '>') && r == 2) || \
	((*curr == ')' || *curr == '(' || *curr == '&') && r == 3)))
		status = check_unexpected_token(curr);
	free(nfd);
	return (status);
}

int 		lexic(char *line)
{
	int 	r;
	int 	status;
	int 	count_tokens;

	status = 0;
	count_tokens = 0;
	while (*line && !status)
	{
		line = remove_spaces(line);
		r = lexic_token(&line, 0);
		if (r == 1)
			count_tokens++;
		if (r == 2)
		{
			if (*line == *(line + 1) || \
				(!ft_strncmp(remove_spaces(line + 1), "", 1) && !count_tokens) || \
				(!ft_strncmp(remove_spaces(line + 1), "", 1) && count_tokens && *line == '|'))
				status = check_unexpected_token(line);
			else
				status = check_unexpected_token(line + 1);
			count_tokens = 0;
			line++;
		}
		else if (r == 3)
			status = check_redir_fd(&line);
		else if (r == 4)
			status = check_unexpected_token(line);
//		if (r == 2 && !status)
//			line++;
	}
	return (status);
}