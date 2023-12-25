/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:12:13 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 00:20:21 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_cmd_len(t_comd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	**create_fds(int size)
{
	int	**fd;
	int	i;

	fd = malloc(sizeof(int *) * (size - 1));
	if (!fd)
		return (NULL);
	i = size - 2;
	while (i >= 0)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			return (NULL);
		i--;
	}
	return (fd);
}

void	close_fds_and_free_and_wait_to_set_status(int **fd,
	t_comd *cmd)
{
	int	turns;

	turns = ft_cmd_len(cmd) - 1;
	while (--turns >= 0)
	{
		close(fd[turns][0]);
		close(fd[turns][1]);
		free(fd[turns]);
	}
	free(fd);
	waitpid(-1, &g_ext_status, 0);
	if (WIFEXITED(g_ext_status))
		g_ext_status = WEXITSTATUS(g_ext_status) % 256;
	else if (WIFSIGNALED(g_ext_status))
		g_ext_status += 128;
	while (wait(NULL) > 0)
		;
	signal(SIGQUIT, (void (*)(int))handle_signal_ctrl_c);
	signal(SIGINT, (void (*)(int))handle_signal_ctrl_c);
}

void	final_execute(t_comd *cmd, t_info *info)
{
	if (cmd->inp == -1 || cmd->outp == -1)
		return ;
	if (are_builin(cmd))
		execute_builtins(cmd, info);
	else
		ft_execve(cmd, info);
}

int	are_builin(t_comd *cmd)
{
	if (!ft_strcmp(cmd->argms[0], "echo"))
		return (1);
	if (!ft_strcmp(cmd->argms[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd->argms[0], "pwd"))
		return (1);
	if (!ft_strcmp(cmd->argms[0], "export"))
		return (1);
	if (!ft_strcmp(cmd->argms[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd->argms[0], "env"))
		return (1);
	if (!ft_strcmp(cmd->argms[0], "exit"))
		return (1);
	return (0);
}
