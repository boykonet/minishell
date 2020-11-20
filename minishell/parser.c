#include "../minishell.h"

t_params		*new_param(t_params *params)
{
	t_params	*new;

	if (!(new = malloc(sizeof(t_params))))
		return (NULL);
	new->next = NULL;
	return (new);
}

void		parser(t_data *data, t_list *head, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!params = ft_lstnew(params))
		while (line[i] != '|' || line[i] != ';')
		{

		}
		params = params->next;
	}
}
