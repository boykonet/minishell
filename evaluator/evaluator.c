
#include "minishell.h"
#include "other.h"
#include "parser.h"

t_list			*dollar_tokens(char **line, t_eval *eval)
{
	t_list		*head;
	t_list		*list;
	char 		*token;

	token = return_token(line, eval);
	if (!(head = ft_lstnew(token)))
		exit(errno);
	list = head;
	while (*(*line))
	{
		list->next = ft_lstnew(NULL);
		list = list->next;
	}
	return (head);
}

void			check_lists(t_d **data, t_params *params, t_eval *eval)
{
	t_list		*list;
	t_list		*prev;
	t_list		*tokens;
	char 		*tmp;
	char 		*tmp2;
	char 		*name;
	char 		*redir;

	tmp = NULL;
	list = params->args;
	prev = params->args;
	while (list && eval->exit_status != 2)
	{
		if (!ft_strcmp(tmp, ">>") || !ft_strcmp(tmp, ">") || !ft_strcmp(tmp, "<"))
		{
			open_and_close_fd(list->content, list->next->content, eval, &params);
			if (eval->exit_status == 2)
				break ;
//			delete_list_elem(&params->args, prev->next);
//			delete_list_elem(&params->args, prev->next);
			list = list->next;
		}
		else
		{
			tmp = (char*)list->content;
			list->content = return_token((char**)&list->content, eval);
			//		if (!ft_strcmp(list->content, "") && !eval->quotes && eval->dollar_flag = 1)
			//			delete_list_elem();
			if (ft_strchr(list->content, ' ') && eval->dollar_flag == 1 && !eval->quotes)
			{
				tokens = dollar_tokens((char **) &list->content, eval);
			}
			free(tmp);
			tmp = NULL;
		}
 		list = list->next;
	}
}

void 			init_eval(t_d **data, t_eval *eval, const int *status)
{
	eval->exit_status = (*data)->exit_status == 2 ? 1 : 0;
	eval->dollar_flag = 0;
	eval->env = (*data)->env;
	eval->quotes = 0;
	eval->status = *status;
}

void 			evaluator(t_d **data, t_params *par, int *status)
{
	t_eval		eval;

	init_eval(data, &eval, status);
	while (par)
	{
		check_lists(data, par, &eval);
		if (eval.exit_status == 2 || par->pipe_semic == 2)
			break ;
		par = par->next;
	}
	if (eval.status > 0 && eval.exit_status == 1)
	{
		eval.status = 0;
		eval.exit_status = 0;
	}
	(*data)->exit_status = eval.exit_status;
	*status = eval.status;
}