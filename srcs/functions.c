#include "../minishell.h"

char		*remove_spaces(char *line)
{
	while (*line == ' ')
		line++;
	return (line);
}

char 			**copy_array(char **src)
{
	char 		**res;
	int 		i;

	i = number_of_lines(src);
	if (!(res = ft_calloc(i + 1, sizeof(char*))))
		exit(errno);
	i = 0;
	while (src[i])
	{
		if (!(res[i] = ft_strdup(src[i])))
		{
			free_string(res);
			exit(errno);
		}
		i++;
	}
	return (res);
}