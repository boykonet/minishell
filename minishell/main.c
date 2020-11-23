#include "../minishell.h"

int		main(int argc, char **argv, char **envp)
{
	static t_env	*env = NULL;
	t_env	*tmp = NULL;
	int		len;
	char	**arr;

	env = ft_copy_envirom(envp);
	len = ft_lstsize_env(env);
	// ft_export(argc, argv, env, len);
	ft_env(argc, envp, len);
	return (0);
}
