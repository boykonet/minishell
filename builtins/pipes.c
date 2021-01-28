#include "builtins.h"
#include "other.h"
#include "minishell.h"

int 	check_command(char *cmd)
{
	char 	*arr[] = {"echo", "pwd", "cd", "env", "export", "unset", "exit", NULL};
	int 	count;

	count = 0;
	while (arr[count])
	{
		if (!ft_strncmp(arr[count], cmd, ft_strlen(cmd)))
			return (0);
		count++;
	}
	return (1);
}

int		pipes(t_params *params, t_env **env, int *status)
{
	int		pipefd[2];
	int		origfd[2];
	pid_t	childpid;
	char    **args;
	char 	**envp;
	char	buff[4096];
	int     a;
	int 	len;
	char    *cmd;

	a = 0;
	origfd[0] = dup(STDIN_FILENO);
	origfd[1] = dup(STDOUT_FILENO);
	envp = convert_env_to_arr(*env);
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
			cmd = find_path(params->args->content, find_data_in_env(*env, "PATH", 0));
			args = convert_struct_to_array(params->args);
			if (!check_command(params->args->content))
				builtins(params, env, status);
			else
				a = execve(cmd, args, envp);
			free(cmd);
			free_string(args);
			free_string(envp);
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
	len = read(0, buff, 4095);
	buff[len] = '\0';
	dup2(origfd[0], 0);
	dup2(origfd[1], 1);
//	ft_printf("\e[1;32m%s\e[0m", buff);
	write(1, buff, ft_strlen(buff));
	return (0);
}
