/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_and_start.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 23:29:28 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/23 02:50:04 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// this function appears to tokenize the input command cmd,
//  creating a linked list of tokens stored in data. It detects
//   operators and other symbols, adds them as tokens to the data,
//    determines the type of each token, and checks for syntax errors
//     in the resulting token list. If a syntax error is found, it frees
// 	 the memory and returns 1, indicating an error.
int	tokenize_inp_cmd(char *cmd, t_tkn **data, t_context *context)
{
	int	i;

	i = 0;
	*data = NULL;
	while (cmd[i])
	{
		if (cmd[i] && !check_red_pipe(cmd[i], cmd, i))
			cmd_to_str_add(data, cmd, &i);
		if (cmd[i] && check_red_pipe(cmd[i], cmd, i) && cmd[i] != ' ')
			add_operator_tkn(data, cmd, &i);
		i++;
	}
	modify_cmd_if(data, context);
	if (check_pipe_red_herdoc(data))
		return (free_clen_data(data), 1);
	return (0);
}

// function acts as the entry point for processing a command
//  line input. It performs input validation, tokenization,
//   command generation, data cleanup, and signal handling
//    to ensure the proper initiation of the command processing flow

int	proc_valid_cmd(char *line, t_tkn *data, t_comd **cmd, t_context *cont)
{
	if (check_syx_quotes_err(line))
		return (0);
	if (tokenize_inp_cmd(line, &data, cont))
		return (0);
	handle_get_cmd(&data, cmd, cont);
	free_clen_data(&data);
	if (cont->data->sig == 1)
		return (0);
	return (1);
}
