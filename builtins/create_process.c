#include "minishell.h"

int				create_process(char **args, char **envp, char *cmd)
{
	pid_t 			pid;
	int 			status_code;
	int 			wstatus;
	int 			exit_code;

	wstatus = 0;
	status_code = 0;
	exit_code = EXIT_FAILURE;
	if ((pid = fork()) == -1)
	{
		ft_printf("-minishell: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(cmd, args, envp) < 0)
		{
			ft_putstr_fd("-minishell: ", 1);
			ft_putstr_fd(cmd, 1);
			ft_putendl_fd(": command not found", 1);
			exit_code = 127;
		}
		exit(exit_code);
	}
	else
	{
		waitpid(pid, &wstatus, WUNTRACED);
		if (WIFEXITED(wstatus) > 0)
			status_code = WEXITSTATUS(wstatus);
	}
	return (status_code);
}
