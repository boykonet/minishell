#include "minishell.h"

int				create_process(char **args, char **envp, char *cmd)
{
	pid_t 			pid;
	int 			status_code;
	int 			wstatus;

	wstatus = 0;
	status_code = 0;
	if ((pid = fork()) == -1)
	{
		ft_printf("-minishell: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(cmd, args, envp) < 0)
		{
			ft_printf("-minishell: %s: command not found\n", cmd);
			exit(127);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &wstatus, WUNTRACED);
		if (WIFEXITED(wstatus) > 0)
			status_code = WEXITSTATUS(wstatus);
	}
	return (status_code);
}
