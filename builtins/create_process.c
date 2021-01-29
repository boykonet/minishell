#include "minishell.h"

int				create_process(char **args, char *cmd)
{
	pid_t 			pid;
	int 			status_code;
	int 			wstatus;

	wstatus = 0;
	status_code = 1;
	if ((pid = fork()) == -1)
	{
		ft_printf("-minishell: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(cmd, args, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &wstatus, WUNTRACED);
		if (WIFEXITED(wstatus))
			status_code = WEXITSTATUS(wstatus);
		if (wstatus)
			ft_printf("-minishell: %s: command not found\n", cmd);
	}
	return (status_code);
}
