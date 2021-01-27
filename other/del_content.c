

#include "other.h"

void		del_list_content(void *content)
{
	if (content)
		free(content);
}

void		del_params_content(t_params *params)
{
	if (params->args)
		ft_lstclear(&params->args, del_list_content);
	if (params->in > 2)
		close(params->in);
	if (params->out > 2)
		close(params->out);
	if (params->err > 2)
		close(params->err);
}

void 		del_env_content(t_env *env)
{
	if (env->name)
		free(env->name);
	if (env->value)
		free(env->value);
}