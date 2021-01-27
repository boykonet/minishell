
#include "minishell.h"

int 			number_of_redirect(char *redir)
{
	if (!ft_strncmp(redir, "<", ft_strlen(redir)))
		return (0);
	else if (!ft_strncmp(redir, ">", ft_strlen(redir)) || \
				!ft_strncmp(redir, ">>", ft_strlen(redir)) || \
				!ft_strncmp(redir, "1>", ft_strlen(redir)) || \
				!ft_strncmp(redir, "1>>", ft_strlen(redir)))
		return (1);
	else if (!ft_strncmp(redir, "2>", ft_strlen(redir)) || \
				!ft_strncmp(redir, "2>>", ft_strlen(redir)))
		return (2);
	return (-1);
}
