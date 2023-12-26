/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:48:34 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 03:14:05 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	dups_last_pipe(int **fd, int i, t_comd *cmd)
{
	close(fd[i][1]);
	if (cmd->inp == 0)
		dup2(fd[i][0], cmd->inp);
	dup2(cmd->inp, 0);
	dup2(cmd->outp, 1);
	close(fd[i][0]);
}

void	last_pipe(int **fd, int *i, t_comd *cmd, t_info *info)
{
	int	pid;

	if (!cmd->next)
	{
		g_ext_status = 0;
		if (!cmd->argms)
			return ;
		pid = fork();
		if (pid == -1)
			g_ext_status = 1;
		else if (!pid)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			if (g_ext_status == 1)
				exit(1);
			dups_last_pipe(fd, *i, cmd);
			final_execute(cmd, info);
			exit(g_ext_status);
		}
	}
}
