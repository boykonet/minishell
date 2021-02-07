#include "minishell.h"
#include "other.h"

int			check_word(t_list *str)
{
	t_env	*random;
	char	*buf;
	int		i;
	int		len;

	i = 0;
	random = new_item(str);
	if (!(buf = ft_strdup(random->name)))
		exit(errno);
	len = ft_strlen(buf);
	while (i < len)
	{
		if (i == 0 && !ft_isalpha(buf[i]) && buf[i] != 95)
			return (0);
		if (!ft_isalnum(buf[i]) && !(buf[i] == 95))
			return (0);
		i++;
	}
	return (1);
}
