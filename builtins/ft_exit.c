#include "builtins.h"

int     			ft_exit(t_list *args)
{
	unsigned char			num;
	unsigned long long int	long_num;
	int 					neg;
	int 					overflow;
	char 					*str;

	neg = 1;
	overflow = 0;
	long_num = 0;
	str = NULL;
	if (args)
	{
		str = args->content;
		if (*str == '-')
		{
			neg = -1;
			str++;
		}
		while (!overflow && str && *str >= '0' && *str <= '9')
		{
			long_num = long_num * 10 + *str++ - '0';
			if ((neg == 1 && long_num > LLONGMAX) || (neg == -1 && long_num > (LLONGMAX + 1)))
				overflow = 1;
		}
	}
	ft_putendl_fd("exit", 1);
	if ((args && str && *str) || overflow)
	{
		ft_putstr_fd("-minishell: exit: ", 1);
		ft_putstr_fd(args->content, 1);
		ft_putendl_fd(": numeric argument required", 1);
		long_num = 255;
	}
	num = (unsigned char)((long long int)long_num * neg);
	return ((int)num);
}