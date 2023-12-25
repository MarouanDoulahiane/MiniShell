/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 22:39:04 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/24 21:40:05 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_clen_data(t_tkn **lst)
{
	t_tkn	*tmp;
	t_tkn	*tmp2;

	tmp = *lst;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp2 = tmp->next;
		free_val_tkn(tmp);
		tmp = tmp2;
	}
	*lst = NULL;
}

void	free_val_tkn(t_tkn *lst)
{
	if (lst == NULL)
		return ;
	free(lst->val);
	free(lst);
}

void	ft_add_tkn_back(t_tkn **data, t_tkn *new_dt)
{
	t_tkn	*tmp;

	tmp = *data;
	if (!(*data))
	{
		new_dt->prev = NULL;
		*data = new_dt;
	}
	else
	{
		if (!tmp->next)
		{
			tmp->next = new_dt;
			new_dt->prev = tmp;
			return ;
		}
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_dt;
		new_dt->prev = tmp;
	}
}

t_tkn	*ft_new_tkn(char	*data)
{
	t_tkn	*new_dt;

	new_dt = (t_tkn *)malloc(sizeof(t_tkn));
	if (!new_dt)
		return (0);
	new_dt->type = 1;
	new_dt->val = data;
	new_dt->next = NULL;
	return (new_dt);
}
