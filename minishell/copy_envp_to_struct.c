#include "../minishell.h"

void		*init_name_value(char *str, char *separator, char **name, char **value)
{
	if (!(*name = ft_substr(str, 0, separator - str)))
		return (NULL);
	if (!(*value = ft_substr(separator, 1, ft_strlen(separator + 1))))
		return (NULL);
	return (separator);
}

t_env		*copy_envp_to_struct(char **envp)
{
	t_env	*env;
	t_env	*curr;
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(env = ft_lstnew_env(NULL, NULL)))
		return (NULL);
	curr = env;
	tmp = ft_strchr(envp[i], '=');
	if (!(init_name_value(envp[i], tmp, &curr->name, &curr->value)))
		return (NULL);
	while (envp[++i])
	{
		if (!(curr->next = ft_lstnew_env(NULL, NULL)))
			return (NULL);
		curr = curr->next;
		tmp = ft_strchr(envp[i], '=');
		if (!(init_name_value(envp[i], tmp, &curr->name, &curr->value)))
			return (NULL);
	}
	if (!(curr->next = ft_lstnew_env(ft_strdup("OLDPWD"), NULL)))
		return (NULL);
	return (env);
}