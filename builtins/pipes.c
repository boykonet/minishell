#include "builtins.h"
#include "other.h"
#include "minishell.h"


//int			set_read(int *lpipe)
//{
//	int 	a;
//
//	dup2(lpipe[0], STDIN_FILENO);
//	close(lpipe[0]);
//	close(lpipe[1]);
//	wait(&a);
//	return (a);
//}
//
//void		set_write(t_params *params, t_env **env, int *rpipe, int *status)
//{
//	int 	a;
//	char 	*cmd;
//	char 	**args;
//	char 	**envp;
//
//	a = 0;
//	dup2(rpipe[1], STDOUT_FILENO);
//	close(rpipe[0]);
//	close(rpipe[1]);
//	envp = convert_env_to_arr(*env);
//	cmd = find_path(params->args->content, find_data_in_env(*env, "PATH", 0));
//	args = convert_struct_to_array(params->args);
//	if (!check_command(params->args->content))
//		builtins(params, env, status);
//	else
//		a = execve(cmd, args, envp);
//	free(cmd);
//	free_string(args);
//	free_string(envp);
//	exit(a);
//}
//
//void		fork_and_chain(t_params *params, t_env **env, int *lpipe, int *rpipe, int *status)
//{
//	int childpid;
//
//	if ((childpid = fork()) < 0)
//	{
//		ft_printf("-minishell: fork: %s\n", strerror(errno));
//		exit(EXIT_FAILURE);
//	}
//	if (!childpid)
//	{
//		if (lpipe)
//			set_read(lpipe);
//		if (rpipe)
//			set_write(params, env, rpipe, status);
//	}
//}
//
//int			pipes(t_params *params, t_env **env, int *status)
//{
//	int		lpipe[2];
//	int 	rpipe[2];
//	int 	pipefd[2];
//	char	buff[4096];
//	int 	len;
//	int 	i;
//
//	pipefd[0] = dup(STDIN_FILENO);
//	pipefd[1] = dup(STDOUT_FILENO);
//	len = ft_lstsize_params(params);
//	i = 1;
//	if (pipe(rpipe) == -1)
//	{
//		ft_printf("-minishell: pipe: %s\n", strerror(errno));
//		exit(EXIT_FAILURE);
//	}
//	fork_and_chain(params, env, NULL, rpipe, status);
//	lpipe[0] = rpipe[0];
//	lpipe[1] = rpipe[1];
//	params = params->next;
//	while (i < len - 1)
//	{
//		pipe(rpipe);
//		fork_and_chain(params, env, lpipe, rpipe, status);
//		close(lpipe[0]);
//		close(lpipe[1]);
//		lpipe[0] = rpipe[0];
//		lpipe[1] = rpipe[1];
//		params = params->next;
//		i++;
//	}
//	fork_and_chain(params, env, lpipe, NULL, status);
//	close(lpipe[0]);
//	close(lpipe[1]);
//	len = read(0, buff, 4095);
//	buff[len] = '\0';
//	dup2(pipefd[0], 0);
//	dup2(pipefd[1], 1);
//	write(1, buff, ft_strlen(buff));
//	return (0);
//}

int				pipes(t_d **data)
{
	t_params	*curr;
	int			pipefd[2];
	int			origfd[2];
	pid_t		childpid;
	char		**args;
	char		**envp;
	char		buff[101];
	int			len;
	int			wstatus;
	int 		status;
	char		*cmd;
	char 		*tmp;
	char 		*res;

	origfd[0] = dup(STDIN_FILENO);
	origfd[1] = dup(STDOUT_FILENO);
	wstatus = 0;
	status = 0;
	curr = (*data)->params;
	while (!status && curr)
	{
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
		{
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
			if (!(cmd = find_path(curr->args->content, find_data_in_env((*data)->env, "PATH", 0))))
				if (!(cmd = ft_strdup(curr->args->content)))
					exit(EXIT_FAILURE);
			if (!check_command(curr->args->content))
				wstatus = builtins(data, curr);
			else
			{
				if (execve(cmd, args, envp) < 0)
				{
					ft_putstr_fd("-minishell: ", 2);
					ft_putstr_fd(cmd, 2);
					ft_putendl_fd(": command not found", 2);
					wstatus = 127;
				}
			}
			free(cmd);
			free_string(args);
			free_string(envp);
			exit(wstatus);
		}
		else
		{
			dup2(pipefd[0], 0);
			close(pipefd[0]);
			close(pipefd[1]);
			if (waitpid(childpid, &wstatus, 0) < 0)
			{
				ft_putendl_fd("-minishell: waitpid failed", 2);
				exit(EXIT_FAILURE);
			}
			if (WIFEXITED(wstatus))
				status = WEXITSTATUS(wstatus);
		}
		curr = curr->next;
	}
	res = ft_strdup("");
	while ((len = read(0, buff, 100)) > 0)
	{
		tmp = res;
		buff[len] = '\0';
		if (!(res = ft_strjoin(res, buff)))
			exit(errno);
		free(tmp);
	}
	dup2(origfd[0], 0);
	dup2(origfd[1], 1);
	ft_putstr_fd(res, 1);
	free(res);
	return (status);
}