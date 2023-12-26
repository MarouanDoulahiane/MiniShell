/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:56:46 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/12/26 02:02:36 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// this code is a signal handler specifically designed to handle
//  the SIGINT signal, commonly used to handle Ctrl+C interrupts
//   in a terminal-based program. It updates some internal
//    state (g_lb__data.exit_status) and performs some actions to clear
//     the input line and refresh the display to provide a smooth user
// 	 experience when the program is interrupted.
void	handle_signal_ctrl_c(int sig, t_context *ptr)
{
	static t_context	*context;

	if (sig == -200)
		context = ptr;
	if (waitpid(-1, NULL, WNOHANG) == 0)
	{
		printf("\n");
		return ;
	}
	if (sig == SIGINT)
	{
		g_ext_status = 1;
		if (!context->data->sigflg)
			ft_putstr("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
// function is responsible for setting up signal handling and managing
// input/output redirection for the program. It redirects standard
//  input and standard output, sets the action for certain
//  signals (ignoring SIGQUIT and using the handler function for SIGINT),
//   and resets some internal state related to signal handling.

void	handle_signal_in_out(t_context *context)
{
	dup2(context->data->f_stdin, 0);
	dup2(context->data->f_stdout, 1);
	context->data->sig = 0;
	handle_signal_ctrl_c(-200, context);
	signal(SIGQUIT, (void (*)(int))handle_signal_ctrl_c);
	signal(SIGINT, (void (*)(int))handle_signal_ctrl_c);
}

//simple shell loop that reads input, processes commands, and executes
void	loop_and_process_exec_cmd(t_tkn *data, t_comd *cmd, t_context *context,
	t_info *info)
{
	char	*ln;

	while (1)
	{
		handle_signal_in_out(context);
		ln = readline("\033[1;32m:)\033[0m Minishell: $ ");
		context->data->sigflg = 0;
		if (!ln)
		{
			printf("exit\n");
			break ;
		}
		if (ln[0])
		{
			add_history(ln);
			if (proc_valid_cmd(ln, data, &cmd, context))
			{
				add_history(ln);
				excute(cmd, context, info);
				free_node_clean(&cmd);
			}
		}
		free(ln);
	}
}

int	main(int ac, char **av, char **env)
{
	t_tkn		*data;
	t_comd		*cmd;
	t_context	*context;
	t_info		*info;

	(void)av;
	g_ext_status = 0;
	rl_catch_signals = 0;
	printf("%s\n", START);
	if (!isatty(0))
		return (0);
	if (ac == 1)
	{
		info = initialize_data(env);
		if (info == NULL)
			exit(1);
		context = initialize_context(info->envp);
		if (context == NULL)
			exit(1);
		context->data->f_stdin = dup(0);
		context->data->f_stdout = dup(1);
		data = malloc(sizeof(t_tkn *));
		if (!data)
			exit(1);
		cmd = NULL;
		loop_and_process_exec_cmd(data, cmd, context, info);
		free(data);
		free(context);
	}
	exit(g_ext_status);
}
