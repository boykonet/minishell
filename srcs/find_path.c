/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 11:49:13 by snaomi            #+#    #+#             */
/*   Updated: 2021/01/23 17:55:53 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				create_process(char *cmd)
{
	pid_t 			pid;
	int 			status_code;
	int 			wstatus;
	char *const		parm_list[] = {"", NULL};

	wstatus = 0;
	status_code = 1;
	if ((pid = fork()) == -1)
	{
		ft_printf("-minishell: fork failed\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(cmd, parm_list, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &wstatus, WUNTRACED);
		if (WIFEXITED(wstatus))
			status_code = WEXITSTATUS(wstatus);
	}
	return (status_code);
}

char				*find_path(char *old_cmd, char *path)
{
	char			*tmp;
	char 			*cmd;
	char			**dirs;
	DIR				*name;
	struct dirent	*entry;
	int				i;
	int				j;
	int				flag;

	flag = 1;
	j = 0;
	dirs = NULL;
	if (path)
		dirs = ft_split(path, ':');
	i = number_of_lines(dirs);
	while (j < i)
	{
		cmd = NULL;
		name = NULL;
		if (!(name = opendir(dirs[j])))
			return (NULL);
// The readdir() function returns a pointer
// to a dirent structure, or NULL if an error occurs or end of the directory stream is reached. 
// On error, errno is set appropriately. 
		while ((entry = readdir(name)))
		{
// d_name - Это поле содержит имя файла с завершающим null.
			if (!ft_strncmp(entry->d_name, old_cmd, ft_strlen(entry->d_name)))
			{				
				if (!(tmp = ft_strjoin(dirs[j], "/")))
					exit(errno);
				if (!(cmd = ft_strjoin(tmp, old_cmd)))
					exit(errno);
				free(tmp);
				if (!(flag = create_process(cmd)))
					break ;
				free(cmd);
			}
		}
		closedir(name);
		if (!flag)
			return (cmd);
		j++;
	}
	return (NULL);
}
//
//int 	main(int argc, char **argv, char **envp)
//{
//	t_env	*env;
//	char 	*str;
//
//	env = copy_envp_to_struct(envp);
//	str = find_path("aaa", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");
//	printf("%s\n", str);
//	free(str);
//	return (0);
//}