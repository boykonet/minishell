#include "builtins.h"

int     ft_exit(void)
{
	write(1, "exit\n", 5);
	return (0);
}