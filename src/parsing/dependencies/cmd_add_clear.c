/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 23:44:05 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/06 19:55:06 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	cmd_size(t_comd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

void	free_node_clean(t_comd **cmd)
{
	t_comd	*tmp ;
	t_comd	*tmp2;

	if (!cmd)
		return ;
	tmp = *cmd;
	while (tmp)
	{
		tmp2 = tmp->next;
		free_arg_cmd(tmp);
		tmp = tmp2;
	}
	*cmd = NULL;
}

void	free_arg_cmd(t_comd *cmd)
{
	if (!cmd)
		return ;
	free(cmd->comd);
	free_tab(cmd->argms);
	free(cmd);
}

void	add_cmd_back(t_comd **cmd, t_comd *new_c)
{
	t_comd	*tmp;

	if (!cmd || !new_c)
		return ;
	if (!*cmd)
	{
		*cmd = new_c;
		return ;
	}
	tmp = ft_lastcmd_node(*cmd);
	tmp->next = new_c;
}

t_comd	*ft_lastcmd_node(t_comd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next != NULL)
	{
		cmd = cmd->next;
	}
	return (cmd);
}
