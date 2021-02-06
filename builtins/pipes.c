#include "builtins.h"
#include "other.h"
#include "minishell.h"

static int 		child_proc_pipes_cmd(t_d **data, t_params *curr, char **args, char **envp)
{
	int 		status;
	char 		*cmd;

	status = 0;
	if (!(cmd = find_path(curr->args->content, \
	find_data_in_env((*data)->env, "PATH", 0))))
		if (!(cmd = ft_strdup(curr->args->content)))
			exit(EXIT_FAILURE);
	if (!check_command(curr->args->content))
		status = builtins(data, curr);
	else
	{
		if (execve(cmd, args, envp) < 0)
		{
			ft_putstr_fd("-minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": command not found", 2);
			status = 127;
		}
	}
	free(cmd);
	return (status);
}

static int 		child_proc_pipes(t_d **data, t_params *curr, int *pipefd)
{
	int 		status;
	char 		**envp;
	char 		**args;

	if (curr->in > 2)
		dup2(curr->in, 0);
	if (curr->out > 2)
		dup2(curr->out, 1);
	else
		dup2(pipefd[1], 1);
	close(pipefd[0]);
	close(pipefd[1]);
	envp = convert_env_to_arr((*data)->env);
	args = convert_struct_to_array(curr->args);
	status = child_proc_pipes_cmd(data, curr, args, envp);
	free_string(args);
	free_string(envp);
	exit(status);
}

static int 		parent_proc_pipes(t_d **data, int *pipefd, int childpid)
{
	int 		status;

	status = 0;
	(*data)->flag = 1;
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	close(pipefd[1]);
	if (waitpid(childpid, &status, 0) < 0)
	{
		ft_putendl_fd("-minishell: waitpid failed", 2);
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	return (status);
}

static int 		pipes_in_work(t_d **data, t_params *curr)
{
	int 		pipefd[2];
	int 		childpid;
	int 		status;

	childpid = 0;
	status = 0;
	if (pipe(pipefd) == -1)
	{
		ft_putendl_fd("-minishell: pipe failed", 2);
		exit(EXIT_FAILURE);
	}
	if ((childpid = fork()) < 0)
	{
		ft_putendl_fd("-minishell: fork failed", 2);
		exit(EXIT_FAILURE);
	}
	if (!childpid)
		status = child_proc_pipes(data, curr, pipefd);
	else
		status = parent_proc_pipes(data, pipefd, childpid);
	return (status);
}

int				pipes(t_d **data)
{
	t_params	*curr;
	int 		status;

	status = 0;
	curr = (*data)->params;
	while (!status && curr)
	{
		status = pipes_in_work(data, curr);
		curr = curr->next;
	}
	read_and_write_pipeline((*data)->origfd);
	(*data)->flag = 0;
	return (status);
}