/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snaomi <snaomi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:34:02 by snaomi            #+#    #+#             */
/*   Updated: 2021/01/29 10:27:59 by snaomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "other.h"
//
//char		**from_list_to_arr(t_env *env, int len)
//{
//	int 	i;
//	char	**arr;
//	char	*tmp;
//	char	equat[2] = {'=', '\0'};
//	t_env	*temp;
//
//	temp = env;
//	i = 0;
//	if(!(arr = ft_calloc(len + 1, sizeof(char*))))
//		return (NULL);
//	while(temp)
//	{
//		if (temp->value)
//		{
//			tmp = ft_strjoin(temp->name, equat);
//			arr[i] = ft_strjoin(tmp, temp->value);
//			free(tmp);
//		}
//		else
//			arr[i] = ft_strjoin(temp->name, equat);
//		i++;
//		temp = temp->next;
//	}
//	return (arr);
//}

void 		print_export(char **str, int len)
{
	int		k;
	int		i;

	k = 0;
	while (k < len)
	{
		i = 0;
		ft_putstr_fd("declare -x ", 1);
		while (str[k][i])
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

static void		swap(char **a, char **b)
{
	char		*t;

	t = *a;
	*a = *b;
	*b = t;
}

//int				ft_strcmp(const char *s1, const char *s2)
//{
//    while (*s1 || *s2)
//    {
//        if (*s1 != *s2)
//            return ((unsigned char)*s1 - (unsigned char)*s2);
//        s1++;
//        s2++;
//    }
//    return (0);
//}

static int relative_position(char **arr, int low, int high)
{
	char 	*pivot;
	int 	i;
	int 	j;

	j = low;
	i = low - 1;

	pivot = arr[high];
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

static void		quicksort(char **arr, int low, int high)
{
	int			index;

	index = 0;
	if (low < high)
	{
		index = relative_position(arr, low, high);
		quicksort(arr, low, index - 1);
		quicksort(arr, index + 1, high);
	}
}

//static void		free_head(t_env **head)
//{
//	t_env *tmp;
//
//	tmp = *head;
//	if (*head)
//		*head = (*head)->next;
//	free(tmp);
//}

//char		**ft_split_by_colon(char *str, char c)
//{
//	int		i;
//	char	**arr;
//	char	*tmp;
//	char 	*buf;
//
//	i = 0;
//	buf = str;
//	while ((tmp = ft_strchr(str, c)) && *str != '\0')
//	{
//		tmp++;
//		str = tmp;
//		i++;
//	}
//	if (!(arr = (char**)malloc(sizeof(char*) * (i + 1))))
//		exit(errno);
//	i = 0;
//	str = buf;
//	while ((tmp = ft_strchr(str, c)) && *str != '\0')
//	{
//		if (!(arr[i] = ft_substr(str, 0, tmp - str)))
//			exit(errno);
//		tmp++;
//		str = tmp;
//		i++;
//	}
//	if (!(arr[i] = ft_strdup(str)))
//		exit(errno);
//	arr[i + 1] = NULL;
//	return (arr);
//}

//void		*ft_split_by_quation(char *str, t_env *lst, char c)
//{
//	char	*tmp;
//
//	tmp = ft_strchr(str, c);
//	lst->name = ft_substr(str, 0, tmp - str);
//	lst->value = ft_substr(tmp, 1, ft_strlen(str));
//	if (!lst->name || !lst->value)
//		exit(errno);
//	return (tmp);
//}
//
//int			ft_lstsize_env(t_env *lst)
//{
//	t_env	*temp;
//	int		i;
//
//	i = 0;
//	temp = lst;
//	while (temp)
//	{
//		i++;
//		temp = temp->next;
//	}
//	return (i);
//}

//t_env		*new_item(t_list *item)
//{
//	t_env 	*random;
//
//	random = ft_lstnew_env(NULL, NULL);
//	if (ft_strchr(item->content, '='))
//		ft_split_by_quation(item->content, random, '=');
//	else
//		random->name = ft_strdup(item->content);
//	return (random);
//}

//int			check_word(t_list *str)
//{
//	char 	*buf;
//	int		i;
//	int		len;
//	t_env 	*random;
//
//	i = 0;
//	random = new_item(str);
//	if (!(buf = ft_strdup(random->name)))
//		exit(errno);
//	len = ft_strlen(buf);
//	while (i < len)
//	{
//		if (i == 0 && !ft_isalpha(buf[i]) && buf[i] != 95)
//			return (0);
//		i++;
//		if (ft_isalnum(buf[i]) || buf[i] == 95)
//			return (1);
//	}
//	return (0);
//}

//int         check_word(t_list *str)
//{
//	char    *buf;
//	int     i;
//	int     len;
//	t_env   *random;
//
//	i = 0;
//	random = new_item(str);
//	if (!(buf = ft_strdup(random->name)))
//		exit(errno);
//	len = ft_strlen(buf);
//	while (i < len)
//	{
//		if (i == 0 && !ft_isalpha(buf[i]) && buf[i] != 95)
//			return (0);
//		if (!ft_isalnum(buf[i]) && !buf[i] == 95)
//			return (0);
//		i++;
//	}
//	return (1);
//}

int			ft_export(t_env **env, t_params *argv)
{
	char 	**arr;
	int		len;
	t_env 	*random;
	t_env 	*buf;

	buf = *env;
	while (argv->args->next)
	{
		argv->args = argv->args->next;
		if (check_word(argv->args))
		{
			random = new_item(argv->args);
			while (buf)
			{
				if (!ft_strcmp(random->name, buf->name))
				{
					if (random->value)
					{
						buf->value = random->value;
						return (0);
					}
					else
						return (0);
				}
				buf = buf->next;
			}
			ft_lstadd_back_env(env, random);
			buf = *env;
		}
		else
		{
			ft_putstr_fd("minishell: export: `", 1);
			ft_putstr_fd(argv->args->content, 1);
			ft_putstr_fd("': not a valid identifier", 1);
			ft_putchar_fd('\n', 1);
		}
	}
	if (!ft_strncmp(argv->args->content, "export", ft_strlen(argv->args->content)))
	{
		len = ft_lstsize_env(buf);
		arr = convert_env_to_arr(buf);
		quicksort(arr, 0, len - 1);
		print_export(arr, len);
		free_string(arr);
	}
	return (0);
}
