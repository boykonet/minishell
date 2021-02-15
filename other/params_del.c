#include "minishell.h"
#include "other.h"

void			params_delete(t_params **head, t_params *d)
{
	t_params	**elem;

	elem = head;
	while (elem && (*elem) && (*elem) != d)
		elem = &(*elem)->next;
	if (elem && *elem)
	{
		*elem = (*elem)->next;
		del_params_content(d);
		free(d);
	}
}
