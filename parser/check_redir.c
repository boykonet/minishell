#include "builtins.h"
#include "other.h"
#include "parser.h"
#include "minishell.h"

int 		check_redir(char **line)
{
	char 	*curr_str;
	char 	*str;
	char	symb;
	int 	r;

	r = -1;
	if (*(*line) == '<' || *(*line) == '>')
	{
		curr_str = (*line);
		symb = *(*line);
		while (*curr_str && *curr_str == symb && *curr_str != ' ')
			curr_str++;
		if (!(str = ft_substr((*line), 0, curr_str - (*line))))
			exit(errno);
		r = number_of_redirect(str);
		free(str);
	}
	return (r);
}