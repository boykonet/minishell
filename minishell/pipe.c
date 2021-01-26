int		pipes(char **args, char **envp)
{
	int		pipefd[2];
	pid_t	childpid;

	pipe(pipefd);
	if ((childpid = fork()) == -1)
	{
		ft_printf("-minishell: %s: %s\n", );
		write(fd, strerror(errno), ft_strlen(strerror(errno)));
		exit(1);
	}
	if (childpid == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
		execve("/usr/bin/grep", "meta", NULL);
		exit(0);
	}
	else
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		execve("/bin/cat", "meta.c", NULL);
	}
	return (status);
}
