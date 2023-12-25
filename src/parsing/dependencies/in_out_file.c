/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:52:12 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/25 02:26:45 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// function handles the logic for managing output file
//  redirection in a shell program, including error
//  handling for ambiguous redirects and file opening failures.

void	update_outfile(t_comd **command, char *file_path, t_tkn *token)
{
	if (!ft_strcmp(file_path, "\b"))
	{
		g_ext_status = 1;
		ft_putstr("\033[1;31m:(\033[0m Minishell: ambiguous redirect\n", 2);
		(*command)->outp = -1;
		(*command)->errp = 0;
		token->error = 1;
	}
	if ((*command)->outp != -1)
	{
		(*command)->outp = open(file_path, O_CREAT | O_TRUNC | O_RDWR, 0777);
		if ((*command)->outp == -1)
		{
			g_ext_status = 1;
			ft_putstr("\033[1;32m:)\033[0m Minishell: ", 2);
			perror(file_path);
			(*command)->errp = 0;
			token->error = 1;
		}
	}
}
// the function seems to handle file input redirection for a shell-like program.
//  It first checks if the value is a backspace character, and if not,
//   it attempts to open the file specified by value for reading.
//  It also handles error scenarios by setting appropriate error codes
//and messages.

void	check_red_open(t_comd **cmd, char *val, t_tkn *ptr)
{
	if (!ft_strcmp(val, "\b"))
	{
		g_ext_status = 1;
		ft_putstr("\033[1;31m:(\033[0m Minishell: ambiguous redirect\n", 2);
		(*cmd)->inp = -1;
		(*cmd)->errp = 0;
		g_ext_status = ERRR;
		ptr->error = 1;
	}
	if ((*cmd)->inp != -1)
	{
		(*cmd)->inp = open(val, O_RDONLY);
		if ((*cmd)->inp == -1)
		{
			g_ext_status = 1;
			(ft_putstr("\033[1;31m:(\033[0m Minishell: ", 2), perror(val));
			(*cmd)->errp = 0;
			g_ext_status = ERRR;
			ptr->error = 1;
		}
	}
}

// In summary, this function seems to handle file redirection and error
//  handling in a shell-like program. It checks if the file should be
//   created or appended to, and it updates the appropriate fields and
//   error statuses based on the outcome of these operations.

void	check_append_outerr(t_comd **cmd, char *val, t_tkn *ptr)
{
	if (!ft_strcmp(val, "\b"))
	{
		g_ext_status = 1;
		ft_putstr("\033[1;31m:(\033[0m Minishell: ambiguous redirect\n", 2);
		(*cmd)->outp = -1;
		(*cmd)->errp = 0;
		ptr->error = 1;
	}
	if ((*cmd)->outp != -1)
	{
		(*cmd)->outp = open(val, O_CREAT | O_APPEND | O_RDWR, 0777);
		if ((*cmd)->outp == -1)
		{
			g_ext_status = 1;
			ft_putstr("\033[1;31m:(\033[0m Minishell: ", 2);
			perror(val);
			(*cmd)->errp = 0;
			ptr->error = 1;
		}
	}
}
// function is responsible for determining whether a specific condition,
//  related to the err property of tokens in a linked list,
//  is met during traversal. This function is likely used in the context
//   of controlling the flow of operations within a shell program based on
//    the presence of errors or specific token types in the command input.

int	check_err_pipe(t_tkn *data)
{
	t_tkn	*ptr;

	ptr = data;
	while (ptr->prev && ptr->type != PIPE)
	{
		if (ptr->error == 1)
			return (0);
		ptr = ptr->prev;
	}
	return (1);
}
//  function serves as a dispatcher for different types of file
//  input and output operations based on the type of token encountered
//  and the result of the <heck_err_pipe> function. It plays a key role in
//  coordinating the handling of input and output operations within
//  the context of a larger shell program.

void	handle_in_out(t_tkn *ptr, t_comd **cmd)
{
	if (ptr->type == INF && check_err_pipe(ptr))
		check_red_open(cmd, ptr->val, ptr);
	else if (ptr->type == OUTF && check_err_pipe(ptr))
		update_outfile(cmd, ptr->val, ptr);
	else if (ptr->type == PEND && check_err_pipe(ptr))
		check_append_outerr(cmd, ptr->next->val, ptr);
	else if (ptr->type == HERDOC && check_err_pipe(ptr))
		check_red_open(cmd, ptr->next->val, ptr);
}
