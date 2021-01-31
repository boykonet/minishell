#include "builtins.h"

int     			ft_exit(t_list *args)
{
	unsigned char	num;

	num = 0;
	if (args)
		num = (unsigned char)ft_atoi(args->content);
	ft_putendl_fd("exit", 1);
	return ((int)num);
}