/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 21:05:19 by gkarina           #+#    #+#             */
/*   Updated: 2020/11/23 18:46:30 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_echo(char **arg, int fd)
{
	int		i;
	int		back_slash;

	i = 1;
	back_slash = 0;
	if (ft_strnstr(arg[i], "-n", ft_strlen(arg[i])))
		back_slash = 1;
	while (arg[i])
	{
		write(fd, arg[i], ft_strlen(arg[i]));
/* последний пробел не распечатывается!!!*/
		write(fd, " ", 1);
	}
	if (back_slash != 1)
		write(fd, "\n", 1);
}

// size_t		ft_strlen_ch(const char *str)
// {
// 	int			i;

// 	i = 0;
// 	if (!str)
// 		return (i);
// 	while (str[i] != 0)
// 		i++;
// 	return (i);
// }

static char		*ft_strjoin_fr(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (!s1 && !s2)
		return (0);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (0);
	ft_memmove(str, s1, s1_len);
	ft_memmove(str + s1_len, s2, s2_len);
	str[s1_len + s2_len] = '\0';
	free((char *)s1);
	return (str);
}

char	**from_list_to_arr(t_env *env, int len)
{
	int 	i;
	char	**arr;
	char	*tmp;
	char	equat[2] = {'=', '\0'};
	t_env	*temp;

	temp = env;
	i = 0;
	if(!(arr = (char**)(malloc(sizeof(char*) * len + 1))))
		return (NULL);
	while(temp->next != NULL)
	{
		tmp = ft_strjoin_fr(temp->name, equat);
		arr[i] = ft_strjoin_fr(tmp, temp->value);
		i++;
		temp = temp->next;
	}
	tmp = ft_strjoin_fr(temp->name, equat);
	arr[i] = ft_strjoin_fr(tmp, temp->value);
	return (arr);
}

static void print_export(char **str, int len)
{
	int k;
	int i;

	k = 0;
	while(k < (len - 1))
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while (str[k][i] != '\0')
		{
			ft_putchar_fd(str[k][i++], 1);
			if (str[k][i - 1] == '=')
				break ;
		}
		ft_putchar_fd('"', 1);
		while (str[k][i] != '\0')
			ft_putchar_fd(str[k][i++], 1);
		ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		k++;
	}
}

static void swap(char **a, char **b)
{
	char *t = *a;

	*a = *b;
	*b = t;
}

static int     ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 || *s2)
    {
        if (*s1 != *s2)
            return ((unsigned char)*s1 - (unsigned char)*s2);
        s1++;
        s2++;
    }
    return (0);
}

static int relative_position(char **arr, int low, int high)
{
	char *pivot = arr[high];
	int i = (low - 1);
	int j = low;

	while (j <= high)
	{
		if (ft_strcmp(arr[j], pivot) < 0)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

static void	quicksort(char **arr, int low, int high)
{
	int index;
	int k;	

	k = 0;
	if(low < high)
	{
		index = relative_position(arr, low, high);
		quicksort(arr, low, index - 1);
		quicksort(arr, index + 1, high);
	}
}

static t_env		*ft_lstnew_env(char *name, char *value)
{
	t_env *tmp;

	tmp = (t_env*)malloc(sizeof(*tmp) * 1);
	if (tmp)
	{
		tmp->name = name;
		tmp->value = value;
		tmp->next = NULL;
		return (tmp);
	}
	else
		return (0);
}

static void		free_head(t_env **head)
{
	t_env *tmp;

	tmp = *head;
	if (*head)
		*head = (*head)->next;
	free(tmp);
}

int		ft_lstsize_env(t_env *lst)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = lst;
	if (temp)
	{
		while (temp != 0)
		{
			i++;
			temp = temp->next;
		}
		return (i);
	}
	return (0);
}

void	ft_lstadd_back_env(t_env *lst, t_env *new)
{
	t_env *temp;

	temp = lst;
	if (temp)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		lst = new;
}

t_env	*ft_copy_envirom(char **envp)
{
	t_env	*env = NULL;
	t_env	*tmp;
	char	**arr;
	int 	len;	

	len = 1;


	arr = ft_split_env(envp[0], '=');
	if(!(tmp = ft_lstnew_env(arr[0], arr[1])))
		return (NULL);
	env = tmp;
	while(envp[len])
	{
		arr = ft_split_env(envp[len], '=');
		ft_lstadd_back_env(tmp, ft_lstnew_env(arr[0], arr[1]));
		len++;
	}
	return (env);
}

void	ft_export(int argc, char **argv, t_env *env, int len)
{
	int error;
	char **arr;
	char **tmp;
	static t_env *buf;
	int	i;

	i = 0;
	error = 2;
	buf = env;
	if (argc == 2)
	{
		if (ft_strchr(argv[1], '='))
			tmp = ft_split_env(argv[1], '=');
		else
			tmp[0] = argv[1];
		while(buf->next != NULL)
		{
			if (!ft_strcmp(tmp[0], buf->name))
			{
				buf->value = tmp[1];
				return ;
			}
			buf = buf->next;
		}
		ft_lstadd_back_env(env, ft_lstnew_env(tmp[0], tmp[1]));

		// arr = from_list_to_arr(env, len + 1);
		// while(arr[i])
		// {
		// 	printf("%s\n", arr[i]);
		// 	i++;
		// }
		// print_export(arr, len + 2);
	}
	else if (argc == 1)
	{
		arr = from_list_to_arr(env, len);
		quicksort(arr, 0, len - 1);
		print_export(arr, len);
	}
	else
	{
		while (error < argc)
		{
			ft_putstr_fd("minishell: export: `", 1);
			ft_putstr_fd(argv[error], 1);
			ft_putstr_fd("': not a valid identifier", 1);
			ft_putchar_fd('\n', 1);
			error++;
		}
	}	
}

void	ft_env(int argc, char **envp, int len)
{
	int i;

	i = 0;
	while(envp[i])
		ft_putendl_fd(envp[i++], 1);
}
