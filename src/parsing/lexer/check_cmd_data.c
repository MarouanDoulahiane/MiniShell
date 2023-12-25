/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:55:46 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/26 00:27:38 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	set_type_arg(t_tkn **data)
{
	if (ft_strcmp((*data)->val, "|") == 0)
		(*data)->type = PIPE;
	else if (ft_strcmp((*data)->val, "<<") == 0)
		(*data)->type = HERDOC;
	else if (ft_strcmp((*data)->val, ">>") == 0)
		(*data)->type = PEND;
	else if (ft_strcmp((*data)->val, "<") == 0)
		(*data)->type = INP;
	else if (ft_strcmp((*data)->val, ">") == 0)
		(*data)->type = OUTP;
	else if (!(*data)->prev || (*data)->prev->type == PIPE)
		(*data)->type = CMD;
	else if ((*data)->prev && (*data)->prev->type == HERDOC)
		(*data)->type = DELIM;
	else if ((*data)->prev && (*data)->prev->type == PEND)
		(*data)->type = POUT ;
	else if ((*data)->prev && (*data)->prev->type == OUTP)
		(*data)->type = OUTF;
	else if ((*data)->prev && (*data)->prev->type == INP)
		(*data)->type = INF;
	else
		(*data)->type = ARG;
	return (1);
}

void	modify_cmd_if(t_tkn	**data, t_context *context)
{
	t_tkn	*ptr;

	ptr = *data;
	while (ptr)
	{
		set_type_arg(&ptr);
		if (ptr->type == POUT || ptr->type == OUTF
			|| ptr->type == INF)
		{
			ptr->val = expand_var_str(ptr->val, context);
		}
		else if (ptr->type != DELIM)
		{
			if (ft_strchr(ptr->val, '$') && is_quotes_exist(ptr->val))
				ptr->flg = 1;
			else
				ptr->flg = 0;
			ptr->val = expand_var_char(ptr->val, context);
		}
		ptr = ptr->next;
	}
}
