#include "minishell.h"

int		ft_lstsize_env(t_env *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}