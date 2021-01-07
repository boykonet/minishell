int		main(int argc, char **argv, char **envp)
{
	char	*cmd;
	char	*in_name;
	int		in;
	int		fds_pair[2];
	pid_t	pid;

	cmd = argv[1];
	in_name = argv[2];
	in = open(in_name, O_RDONLY);
	dup2(in, 0);
	close(in);

	pipe(fds_pair);
	pid = fork();

	if (pid == 0)
	{
		dup2(fds_pair[1], 1);
		close(fds_pair[1]);
		execve(cmd, in_name, envp);
	}
}
