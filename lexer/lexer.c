//#include "minishell.h

void 			lexer(t_d **data, t_params *par)
{
	t_params	*curr;
	int 		count;

	curr = par;
	count = 1;
	while (curr && curr->pipes_semic != 2)
		count++;
	while (count > 0)
	{
		count--;
	}
}