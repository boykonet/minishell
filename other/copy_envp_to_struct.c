#include "other.h"

void			init_name_value(char *str, char *separator, char **name, char **value)
{
	*name = ft_substr(str, 0, separator - str);
	*value = ft_substr(separator, 1, ft_strlen(separator + 1));
	if (!(*name) || !(*value))
		exit(errno);
}

t_env		*copy_envp_to_struct(char **envp)
{
	t_env	*env;
	t_env	*curr;
	char	*tmp;
	size_t	i;

	i = 0;
	env = ft_lstnew_env(NULL, NULL);
	curr = env;
	tmp = ft_strchr(envp[i], '=');
	init_name_value(envp[i], tmp, &curr->name, &curr->value);
	while (envp[++i])
	{
		curr->next = ft_lstnew_env(NULL, NULL);
		curr = curr->next;
		tmp = ft_strchr(envp[i], '=');
		init_name_value(envp[i], tmp, &curr->name, &curr->value);
	}
	if (!find_data_in_env(env, "OLDPWD", 0))
	{
		curr->next = ft_lstnew_env(ft_strdup("OLDPWD"), ft_strdup(""));
		if (!curr->next->name || !curr->next->value)
			exit(errno);
	}
	return (env);
}