#include "../minishell.h"

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
	curr->name = ft_substr(envp[i], 0, tmp - envp[i]);
	curr->value = ft_substr(tmp, 1, ft_strlen(envp[i]));
	while (envp[++i])
	{
		if (!(curr->next = ft_lstnew_env(NULL, NULL)))
			return (NULL);
		curr = curr->next;
		tmp = ft_strchr(envp[i], '=');
		curr->name = ft_substr(envp[i], 0, tmp - envp[i]);
		curr->value = ft_substr(tmp, 1, ft_strlen(envp[i]));
	}
	return (env);
}
