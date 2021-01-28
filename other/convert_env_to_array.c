#include "minishell.h"

char		**from_env_to_arr(t_env *env)
{
    int     i;
    char    **arr;
    char    *tmp;
    char    equat[2] = {'=', '\0'};

    i = ft_lstsize_env(env);
    if (!(arr = ft_calloc(i + 1, sizeof(char*))))
        exit(errno);
    i = 0;
    while (env)
    {
        if (env->value)
        {
            if (!(tmp = ft_strjoin(env->name, equat)))
            	exit(errno);
            arr[i] = ft_strjoin(tmp, env->value);
            free(tmp);
        }
        else
            arr[i] = ft_strjoin(env->name, equat);
        if (!arr[i])
        	exit(errno);
        i++;
        env = env->next;
    }
    return (arr);
}
