int		main(int argc, char **argv, char **envp)
{
	/* char	*cmd; */
	/* char	*in_name; */
	/* int		in; */
	int		pipefd[2];
	pid_t	childpid;

	/* cmd = argv[1]; */
	/* in_name = argv[2]; */
	/* in = open(in_name, O_RDONLY); // in = 3; */
	/* dup2(in, 0); */
	/* close(in); */

	pipe(pipefd);

	if ((childpid = fork()) == -1)
	{
		write(fd, strerror(errno), ft_strlen(strerror(errno)));
		exit(1);
	}
	if (childpid == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		execve("/usr/bin/grep", "meta", NULL);
		exit(0);
	}
	else
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		execve("/bin/cat", "meta.c", NULL);
	}
}
