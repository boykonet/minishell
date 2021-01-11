

/* 0 return value have name in needle, 1 return name have value in needle*/

#include "../minishell.h"

void		find_data_in_env(t_env *env, char *needle, char **result, \
			int serial_num)
{
	char	*val;

	val = NULL;
	while (env)
	{
		if (serial_num == 0)
			val = env->name;
		else if (serial_num == 1)
			val = env->value;
		if (!ft_strncmp(val, needle, ft_strlen(needle)))
			break ;
		env = env->next;
	}
	if (!env)
		*result = NULL;
	else if (serial_num == 0)
		*result = env->value;
	else if (serial_num == 1)
		*result = env->name;
}
