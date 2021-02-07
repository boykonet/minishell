#include "other.h"

void		ft_lstadd_back_env(t_env **env, t_env *new)
{
	t_env	*current;
	t_env	*prev;

	current = (*env);
	prev = (*env);
	if (current == NULL)
		(*env) = new;
	else
	{
		while (current != NULL)
		{
			prev = current;
			current = current->next;
		}
		prev->next = new;
	}
}
