
#include "minishell.h"
#include "other.h"
#include "parser.h"
#include "lexic.h"

t_list			*dollar_tokens(char *line, t_eval *eval)
{
	t_list		*head;
	t_list		*list;
	char 		*token;

	list = NULL;
	head = NULL;
	line = remove_spaces(line);
	if (*line)
	{
		token = line;
		if (spec_symb(eval->quotes, 0, *line) > 1)
		{
			lexic_token(&line, 1);
			token = ft_substr(token, 0, line - token);
		}
		else
			token = return_token(&line, eval);
		if (token)
		{
			if (!(head = ft_lstnew(token)))
				exit(errno);
		}
		list = head;
	}
	while (*line)
	{
		line = remove_spaces(line);
		token = line;
		if (*line)
		{
			if (spec_symb(eval->quotes, 0, *line) > 1)
			{
				lexic_token(&line, 2);
				token = ft_substr(token, 0, line - token);
			}
			else
				token = return_token(&line, eval);
			if (token)
			{
				if (!(list->next = ft_lstnew(token)))
					exit(errno);
				list = list->next;
			}
		}
	}
	return (head);
}

void			check_lists(t_params *params, t_eval *eval)
{
	t_list		*list;
	t_list		*next;
	t_list		*tokens;
	t_list		*redir;
	t_list		*name;
	char 		*tmp;
	char 		*tmp2;

	tmp = NULL;
	list = params->args;
	while (list && eval->exit_status != 2)
	{
		if (!ft_strcmp(list->content, ">>") || !ft_strcmp(list->content, ">") || !ft_strcmp(list->content, "<"))
		{
			redir = list;
			name = list->next;
			next = list->next->next;
			open_and_close_fd(redir->content, name->content, eval, &params);
			if (!eval->exit_status)
			{
				lst_delete(&params->args, redir);
				lst_delete(&params->args, name);
			}
			list = next;
		}
		else
		{
			tmp = (char*)list->content;
			next = list->next;
			tmp2 = tmp;
			list->content = return_token(&tmp2, eval);
//			ft_putendl_fd(list->content, 1);
			if (list->content)
			{
				if (!ft_strcmp(list->content, "") && !eval->quotes && eval->dollar_flag == 1)
					lst_delete(&params->args, list);
				else if (ft_strchr(list->content, ' ') && eval->dollar_flag == 1 && !eval->quotes)
				{
					tokens = dollar_tokens(list->content, eval);
					lst_replase(&params->args, &tokens, list);
				}
			}
			free(tmp);
			list = next;
			tmp = NULL;
		}
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

void 			evaluator(t_d **data, t_params **par, int *status)
{
	t_eval		eval;
	t_params	*curr;
	t_params	*next;

	init_eval(data, &eval, status);
	curr = (*par);
	while (curr)
	{
		next = curr->next;
		check_lists(curr, &eval);
		if (!curr->args)
		{
			params_delete(&(*data)->params, curr);
			(*par) = next;
		}
		else
			if (eval.exit_status == 2 || curr->pipe_semic == 2)
				break ;
		curr = next;
	}
	if (eval.status > 0 && eval.exit_status == 1)
	{
		eval.status = 0;
		eval.exit_status = 0;
	}
	(*data)->exit_status = eval.exit_status;
	*status = eval.status;
}