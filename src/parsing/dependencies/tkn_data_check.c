/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_data_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:06:13 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/24 22:50:06 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_reder(int var)
{
	if (var == HERDOC || var == OUTP || var == INP || var == PEND)
		return (1);
	return (0);
}

int	check_reder_tkn(t_tkn **data)
{
	t_tkn	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (is_reder(tmp->type) && !tmp->next)
		{
			ft_putstr("\033[1;31m:(\033[0m Minishell: syntax error near " \
				"unexpected token 'newline'\n", 2);
			return (1);
		}
		if (is_reder(tmp->type) && !tmp->next
			&& (is_reder(tmp->next->type) || tmp->next->type == PIPE))
		{
			ft_putstr("\033[1;31m:(\033[0m Minishell: syntax error near " \
				"unexpected token '", 2);
			ft_putstr(tmp->next->val, 2);
			ft_putstr("'\n", 2);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_pipe_tkn(t_tkn **data)
{
	t_tkn	*ptr;

	ptr = *data;
	while (ptr)
	{
		if (ptr->type == PIPE)
		{
			if (!ptr->next || !ptr->prev)
			{
				ft_putstr("\033[1;31m:(\033[0m Minishell: syntax error" \
					" near unexpected token '|'\n", 2);
				return (1);
			}
			else if (ptr->next && ptr->next->type == PIPE)
			{
				ft_putstr("\033[1;31m:(\033[0m Minishell: syntax error" \
				" near unexpected token '||'\n", 2);
				return (1);
			}
		}
		ptr = ptr->next;
	}
	return (0);
}

int	check_herdoc_tkn(t_tkn **data)
{
	int		i;
	t_tkn	*ptr;

	ptr = *data;
	i = 0;
	while (ptr)
	{
		if (ptr->type == HERDOC)
			i++;
		ptr = ptr->next;
	}
	if (i > 16)
	{
		ft_putstr("\033[1;31m:(\033[0m Minishell: maximum here-document count"
			" exceeded\n", 2);
		return (1);
	}
	return (0);
}

int	check_pipe_red_herdoc(t_tkn **data)
{
	if (check_herdoc_tkn(data))
		return (g_ext_status = ERR1, 1);
	if (check_reder_tkn(data))
		return (g_ext_status = SNTX_ERR, 1);
	if (check_pipe_tkn(data))
		return (g_ext_status = SNTX_ERR, 1);
	return (0);
}
