/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:08:21 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 02:08:02 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_if_execve_fails(char **execve_args, char **envp_array)
{
	free_array(envp_array);
	if (execve_args)
	{
		free(execve_args[0]);
		free(execve_args);
	}
}

void	ft_update_shlvl(char	***envp_array)
{
	char	**tmp;
	char	*to_free;
	char	*shlvl;
	int		i;

	tmp = *envp_array;
	i = 0;
	while (tmp[i])
	{
		if (!ft_strncmp(tmp[i], "SHLVL=", 6))
		{
			to_free = tmp[i];
			shlvl = ft_itoa(ft_atoi(tmp[i] + 6) + 1);
			if (!shlvl)
				return ;
			tmp[i] = ft_strjoin(ft_strdup("SHLVL="), shlvl);
			free(shlvl);
			free(to_free);
			break ;
		}
		i++;
	}
}

void	if_execve_args_null(t_comd *cmd)
{
	if (cmd->comd[0] == '.' && cmd->comd[1] == '/'
		&& !access(&cmd->comd[2], F_OK))
	{
		ft_print_err("minishell: ", cmd->outp);
		ft_print_err(cmd->comd, cmd->outp);
		ft_print_err(": Permission denied\n", cmd->outp);
		g_ext_status = 126;
	}
	else if (cmd->comd[0] == '.' && cmd->comd[1] == '/')
	{
		ft_print_err("minishell: ", cmd->outp);
		ft_print_err(cmd->comd, cmd->outp);
		ft_print_err(": No such file or directory\n", cmd->outp);
		g_ext_status = 127;
	}
	else
	{
		ft_print_err("minishell: ", cmd->outp);
		ft_print_err(cmd->comd, cmd->outp);
		ft_print_err(": command not found\n", cmd->outp);
		g_ext_status = 127;
	}
}

void	ft_execve_helper(t_comd *cmd, t_info *data, int pid, char **execve_args)
{
	data->envp_array = ft_env_to_array(data->envp);
	if (!ft_strcmp(cmd->comd, "./minishell") && data->envp_array)
		ft_update_shlvl(&data->envp_array);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(execve_args[0], execve_args, data->envp_array) == -1)
		{
			ft_print_err("execve: Error \n", cmd->outp);
			free_if_execve_fails(execve_args, data->envp_array);
			g_ext_status = 1;
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &g_ext_status, 0);
		if (WIFSIGNALED(g_ext_status))
			g_ext_status += 128;
		else
			g_ext_status %= 255;
	}
}

void	ft_execve(t_comd *cmd, t_info *data)
{
	int		pid;
	char	**execve_args;

	execve_args = ft_get_execve_args(cmd, data);
	if (!execve_args)
	{
		if_execve_args_null(cmd);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_print_err("fork: Error\n", cmd->outp);
		g_ext_status = 1;
		return (free_if_execve_fails(execve_args, NULL));
	}
	ft_execve_helper(cmd, data, pid, execve_args);
	free_if_execve_fails(execve_args, data->envp_array);
}
