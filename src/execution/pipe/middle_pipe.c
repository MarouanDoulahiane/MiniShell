/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:29:59 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/25 18:48:03 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	dups_middle_pipe(int **fd, int i, t_comd *cmd)
{
	close(fd[i][0]);
	if (cmd->outp == 1)
		dup2(fd[i][1], cmd->outp);
	dup2(cmd->outp, 1);
	close(fd[i][1]);
	if (cmd->inp == 0)
		dup2(fd[i - 1][0], cmd->inp);
	dup2(cmd->inp, 0);
	close(fd[i - 1][0]);
}

void	middle_pipe(int **fd, int *i, t_comd *cmd, t_info *info)
{
	int	pid;

	if (cmd && cmd->next)
	{
		pipe(fd[++(*i)]);
		close(fd[(*i) - 1][1]);
		pid = fork();
		if (pid == -1)
			g_ext_status = 1;
		else if (!pid)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			if (g_ext_status == 1)
				exit(1);
			dups_middle_pipe(fd, *i, cmd);
			final_execute(cmd, info);
			exit(g_ext_status);
		}
	}
}
