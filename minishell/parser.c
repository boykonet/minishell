
#include "../minishell.h"

int 			check_unexpected_token(char **name_fd)
{
	char 		*err[] = {">>", "<<", ";;", "||", "<", ">", "(", ")", ";", "|", "", NULL};
	char 		*tmp;
	int 		i;

	i = 0;
	tmp = *name_fd;
	while (err[i])
	{
		if (**name_fd == *err[i] && !ft_strncmp(err[i], *name_fd, ft_strlen(err[i])))
		{
			if (!ft_strncmp(*name_fd, "", ft_strlen(*name_fd)))
				*name_fd = ft_strdup("newline");
			else
				*name_fd = ft_strdup(err[i]);
			free(tmp);
			if (!*name_fd)
				exit(errno);
			return (0);
		}
		i++;
	}
	return (1);
}

char 			*shape_name_fd(char **line, char *curr, t_env *env, int *status)
{
	char 		symb;
	char 		*name_fd;

	symb = *(*line);
	if (*curr == ';' || *curr == '|')
	{
		while (*curr && *curr == symb && *curr != ' ')
			curr++;
		if (!(name_fd = ft_substr((*line), 0, curr - *(line))))
			exit(errno);
	}
	else
		name_fd = return_token(line, env, status);
	(*line) = curr;
	return (name_fd);
}

int 			redirect_and_name_fd(char **line, t_env *env, int *fd, int *status)
{
	char 		*redir;
	char 		*curr;
	char 		*name_fd;

	curr = (*line);
	while (*curr && *curr == *(*line) && *curr != ' ')
		curr++;
	if (!(redir = ft_substr((*line), 0, curr - (*line))))
		exit(errno);
	curr = remove_spaces(curr);
	(*line) = curr;
	name_fd = shape_name_fd(line, curr, env, status);
	if (!check_unexpected_token(&name_fd))
		*status = error_handling(NULL, name_fd, "syntax error near unexpected token", 2);
	else
	{
		if ((*fd = open_fd(name_fd, redir)) < 0)
			*status = error_handling(NULL, name_fd, strerror(errno), 1);
	}
	free(redir);
	free(name_fd);
	if (*status == 0)
		return (1);
	return (0);
}

int 			reopen_fd(char **line, t_env *env, int *fd, int *status)
{
	if (*fd > 2)
	{
		if (close(*fd) < 0)
			return (0);
	}
	if (!(redirect_and_name_fd(line, env, fd, status)))
		return (0);
	return (1);
}