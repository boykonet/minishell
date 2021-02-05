#include "minishell.h"

int				create_process(t_d **data, char **args, char **envp, char *cmd)
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
		if ((*data)->params->in > 2)
			dup2((*data)->params->in, 0);
		if ((*data)->params->out > 2)
			dup2((*data)->params->out, 1);
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
		(*data)->flag = 1;
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
	(*data)->flag = 0;
	return (status_code);
}
