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

int				pipes(t_params *params, t_env **env, int *status, int *exit_status)
{
	int			pipefd[2];
	int			origfd[2];
	pid_t		childpid;
	char		**args;
	char		**envp;
	char		buff[4096];
	int			len;
	char		*cmd;

	origfd[0] = dup(STDIN_FILENO);
	origfd[1] = dup(STDOUT_FILENO);
	while (params)
	{
		if (pipe(pipefd) == -1)
		{
			ft_putstr_fd("-minishell: pipe: ", 1);
			ft_putendl_fd(strerror(errno), 1);
			exit(EXIT_FAILURE);
		}
		if ((childpid = fork()) < 0)
		{
			ft_putstr_fd("-minishell: fork: ", 1);
			ft_putendl_fd(strerror(errno), 1);
			exit(EXIT_FAILURE);
		}
		if (!childpid)
		{
			dup2(pipefd[1], params->out);
			close(pipefd[0]);
			close(pipefd[1]);
			envp = convert_env_to_arr(*env);
			args = convert_struct_to_array(params->args);
			cmd = find_path(params->args->content, find_data_in_env(*env, "PATH", 0));
			if (!check_command(params->args->content))
				builtins(params, env, status, exit_status);
			else
			{
				if (execve(cmd, args, envp) < 0)
				{
					dup2(origfd[0], 0);
					dup2(origfd[1], 1);
					ft_putstr_fd("-minishell: ", 1);
					ft_putstr_fd(cmd, 1);
					ft_putendl_fd(": command not found", 1);
					*status = 127;
				}
			}
			free(cmd);
			free_string(args);
			free_string(envp);
			if (*status)
				exit(*status);
			exit(EXIT_FAILURE);
		}
		else
		{
			dup2(pipefd[0], params->in);
			close(pipefd[0]);
			close(pipefd[1]);
			waitpid(childpid, status, WUNTRACED);
			if (WIFEXITED(*status) > 0)
			{
				dup2(origfd[0], 0);
				dup2(origfd[1], 1);
				return (WEXITSTATUS(*status));
			}
		}
		params = params->next;
	}
	len = read(0, buff, 4095);
	buff[len] = '\0';
	dup2(origfd[0], 0);
	dup2(origfd[1], 1);
	write(1, buff, ft_strlen(buff));
	return (0);
}