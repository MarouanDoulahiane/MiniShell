/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:54:23 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 02:04:38 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// int	are_builin(t_comd *cmd)
// {
// 	if (!ft_strcmp(cmd->argms[0], "echo"))
// 		return (1);
// 	if (!ft_strcmp(cmd->argms[0], "cd"))
// 		return (1);
// 	if (!ft_strcmp(cmd->argms[0], "pwd"))
// 		return (1);
// 	if (!ft_strcmp(cmd->argms[0], "export"))
// 		return (1);
// 	if (!ft_strcmp(cmd->argms[0], "unset"))
// 		return (1);
// 	if (!ft_strcmp(cmd->argms[0], "env"))
// 		return (1);
// 	if (!ft_strcmp(cmd->argms[0], "exit"))
// 		return (1);
// 	return (0);
// }

void	ft_execve_pipe(t_comd *cmd, t_info *data)
{
	int			**fd;
	int			i;
	int			size;
	t_comd		*temp;

	size = ft_cmd_len(cmd);
	fd = create_fds(size);
	if (!fd)
		return ;
	i = 0;
	temp = cmd;
	while (temp->next)
	{
		first_pipe(fd, &i, temp, data);
		temp = temp->next;
		last_pipe(fd, &i, temp, data);
		middle_pipe(fd, &i, temp, data);
	}
	close_fds_and_free_and_wait_to_set_status(fd, cmd);
}

void	run_execve_in_new_fork(t_comd *cmd, t_info *info)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		g_ext_status = 1;
		return ;
	}
	else if (!pid)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		dup2(cmd->inp, 0);
		dup2(cmd->outp, 1);
		ft_execve(cmd, info);
		exit(g_ext_status);
	}
	if (pid)
	{
		waitpid(pid, &g_ext_status, 0);
		if (WIFSIGNALED(g_ext_status))
			g_ext_status += 128;
		else
			g_ext_status = WEXITSTATUS(g_ext_status) % 256;
	}
}

void	excute_via_pipe(t_comd *cmd, t_context *context, t_info *info)
{
	if (!cmd->next)
	{
		if (cmd->inp == -1 || cmd->outp == -1)
			return ;
		run_execve_in_new_fork(cmd, info);
		handle_signal_ctrl_c(-200, context);
		signal(SIGQUIT, (void (*)(int))handle_signal_ctrl_c);
		signal(SIGINT, (void (*)(int))handle_signal_ctrl_c);
	}
	else
	{
		if (cmd->inp == -1 || cmd->outp == -1)
			return ;
		ft_execve_pipe(cmd, info);
	}
}

void	excute(t_comd *cmd, t_context *context, t_info *info)
{
	if (!cmd || !cmd->argms)
		return ;
	if (!cmd->next && are_builin(cmd) && cmd->errp)
	{
		if (!ft_strcmp(cmd->argms[0], "echo"))
			ft_echo(cmd);
		else if (!ft_strcmp(cmd->argms[0], "env"))
			ft_env(cmd, info);
		else if (!ft_strcmp(cmd->argms[0], "cd"))
			ft_cd(cmd, info);
		else if (!ft_strcmp(cmd->argms[0], "pwd"))
			ft_pwd(info, cmd);
		else if (!ft_strcmp(cmd->argms[0], "export"))
			ft_export(cmd, info);
		else if (!ft_strcmp(cmd->argms[0], "unset"))
			ft_unset(cmd, info);
		else if (!ft_strcmp(cmd->argms[0], "exit"))
			ft_exit(cmd);
	}
	else
		excute_via_pipe(cmd, context, info);
}
