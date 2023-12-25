/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:27:13 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/24 06:37:46 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	command_init(t_comd	*cmd)
{
	cmd->argms = NULL;
	cmd->comd = NULL;
	cmd->errp = 1;
	cmd->next = NULL;
	cmd->inp = 0;
	cmd->outp = 1;
}

void	add_cmd_list(t_comd **cmd, t_comd **new_c)
{
	add_cmd_back(cmd, *new_c);
	*new_c = (t_comd *)malloc(sizeof(t_comd));
	command_init(*new_c);
}

void	check_update_cmd(t_comd **new_c)
{
	if ((*new_c)->comd)
		free ((*new_c)->comd);
	(*new_c)->comd = ft_strdup((*new_c)->argms[0]);
	if (check_cmd_isdretory((*new_c)->comd))
		(*new_c)->inp = -1;
}

// his code seems to be handling the expansion and manipulation
//  of command arguments based on certain conditions and the contents
//   of the t_tkn structure ptr.
void	handle_get_cmd(t_tkn **data, t_comd **cmd, t_context *context)
{
	t_tkn	*ptr;
	t_comd	*new_c;

	new_c = NULL;
	add_cmd_list(cmd, &new_c);
	ptr = *data;
	if (process_heredoc(data, context))
		return (free_node_clean(&new_c));
	while (ptr)
	{
		if (ptr->type == CMD || ptr->type == ARG)
			expand_check_update_cmdargs(ptr, new_c);
		else if (ptr->type == PEND || ptr->type == HERDOC
			|| ptr->type == INF || ptr->type == OUTF)
			handle_in_out(ptr, &new_c);
		if ((ptr->next && ptr->next->type == PIPE) || ptr->next == NULL)
			add_cmd_list(cmd, &new_c);
		ptr = ptr->next;
	}
	free(new_c);
}
