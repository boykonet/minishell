#include "minishell.h"

void		*ft_split_by_quation(char *str, t_env *lst, char c)
{
	char	*tmp;
	tmp = ft_strchr(str, c);
	lst->name = ft_substr(str, 0, tmp - str);
	if (*(tmp + 1) == '\0')
		lst->value = ft_strdup("");
	else
		lst->value = ft_substr(tmp, 1, ft_strlen(str));
	if (!lst->name)
		exit(errno);
	return (tmp);
}

char		**ft_split_by_colon(char *str, char c)
{
	int		i;
	char	**arr;
	char	*tmp;
	char	*buf;

	i = 0;
	buf = str;
	while ((tmp = ft_strchr(str, c)) && *str != '\0')
	{
		tmp++;
		str = tmp;
		i++;
	}
	if (!(arr = ft_calloc(i + 1, sizeof(char*))))
		exit(errno);
	i = 0;
	str = buf;
	while ((tmp = ft_strchr(str, c)) && *str != '\0')
	{
		if (!(arr[i] = ft_substr(str, 0, tmp - str)))
			exit(errno);
		tmp++;
		str = tmp;
		i++;
	}
	if (!(arr[i] = ft_strdup(str)))
		exit(errno);
	arr[i + 1] = NULL;
	return (arr);
}
