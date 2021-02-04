#include "minishell.h"

int				create_process(char **args, char **envp, char *cmd, int in, int out)
{
	pid_t 			pid;
	int 			status_code;
	int 			wstatus;
	int 			exit_code;
	int 			origfd[2];

	wstatus = 0;
	status_code = 0;
	exit_code = 0;
	origfd[0] = dup(STDIN_FILENO);
	origfd[1] = dup(STDOUT_FILENO);
	if ((pid = fork()) == -1)
	{
		ft_putendl_fd("-minishell: fork failed", 2);
		exit(EXIT_FAILURE);
	}
	if (!pid)
	{
		if (in > 2)
			dup2(in, 0);
		if (out > 2)
			dup2(out, 1);
		if (execve(cmd, args, envp) < 0)
		{
			ft_putstr_fd("-minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": command not found", 2);
			exit_code = 127;
		}
		exit(exit_code);
	}
	else
	{
		if (waitpid(pid, &wstatus, WUNTRACED) < 0)
		{
			ft_putendl_fd("-minishell: waitpid failed", 2);
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(wstatus) > 0)
			status_code = WEXITSTATUS(wstatus);
	}
	dup2(origfd[0], 0);
	dup2(origfd[1], 1);
	return (status_code);
}
