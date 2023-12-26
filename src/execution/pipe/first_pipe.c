/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:15:06 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 03:16:12 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	dups_first_pipe(int **fd, int i, t_comd *cmd)
{
	close(fd[i][0]);
	dup2(cmd->inp, 0);
	if (cmd->outp == 1)
		dup2(fd[i][1], cmd->outp);
	dup2(cmd->outp, 1);
	close(fd[i][1]);
}

void	first_pipe(int **fd, int *i, t_comd *cmd, t_info *info)
{
	int		pid;

	if (!(*i))
	{
		pipe(fd[*i]);
		pid = fork();
		if (pid == -1)
			g_ext_status = 1;
		else if (!pid)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			dups_first_pipe(fd, *i, cmd);
			final_execute(cmd, info);
			exit(g_ext_status);
		}
	}
}
