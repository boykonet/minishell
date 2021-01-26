#include "../minishell.h"

int		pipes(t_params *params, t_env *env)
{
	int		pipefd[2];
	int		origfd[2];
	pid_t	childpid;
	char    **args;
//	char    buff[4096];
	int     a;
	char    *cmd;

	a = 0;
	origfd[0] = dup(STDIN_FILENO);
	origfd[1] = dup(STDOUT_FILENO);
	while (params)
	{
		if (pipe(pipefd) == -1)
		{
			ft_printf("-minishell: pipe: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if ((childpid = fork()) < 0)
		{
			ft_printf("-minishell: fork: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (!childpid)
		{
			dup2(pipefd[1], 1);
			close(pipefd[0]);
			close(pipefd[1]);
			/*если пайп последний то можно попробовать сделать dup2(origfd[1], 1)*/
			args = convert_struct_to_array(params->args);
			cmd = find_path(params->args->content, find_data_in_env(env, "PATH", 0));
			a = execve(cmd, args, NULL);
			free(cmd);
			free_string(args);
			exit(0);
		}
		else
		{
			dup2(pipefd[0], 0);
			close(pipefd[0]);
			close(pipefd[1]);
			wait(&a);
		}
		params = params->next;
	}
	dup2(origfd[0], 0);
	return (0);
}
