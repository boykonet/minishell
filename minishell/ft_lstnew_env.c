#include "../minishell.h"

t_env		*ft_lstnew_env(void *name, void *value)
{
	t_env	*new;

	if (!(new = malloc(sizeof(t_env))))
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

