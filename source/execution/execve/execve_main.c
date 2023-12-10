/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:08:21 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/10 17:12:28 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

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
			tmp[i] = ft_strjoin("SHLVL=", shlvl);
			free(shlvl);
			free(to_free);
			break ;
		}
		i++;
	}
}

void	if_execve_args_null(t_data *data)
{
	if (data->command[0][0] == '.' && data->command[0][1] == '/'
			&& !access(&data->command[0][2], F_OK))
	{
		ft_print_err("minishell: ");
		ft_print_err(data->command[0]);
		ft_print_err(": Permission denied\n");
	}
	else if (data->command[0][0] == '.' && data->command[0][1] == '/')
	{
		ft_print_err("minishell: ");
		ft_print_err(data->command[0]);
		ft_print_err(": No such file or directory\n");
	}
	else
	{
		ft_print_err("minishell: ");
		ft_print_err(data->command[0]);
		ft_print_err(": command not found\n");
	}
}

void	ft_execve_helper(t_data *data, int pid, char **execve_args)
{
	data->envp_array = ft_env_to_array(data->envp);
	if (!ft_strcmp(data->command[0], "./minishell") && data->envp_array)
		ft_update_shlvl(&data->envp_array);
	if (pid == 0)
	{
		if (execve(execve_args[0], execve_args, data->envp_array) == -1)
		{
			perror("execve: Error \n");
			free_if_execve_fails(execve_args, data->envp_array);
			exit(1);
		}
	}
	else
	{
		if (waitpid(pid, NULL, 0) == -1)
			perror("waitpid: Error \n");
	}
}

void	ft_execve(t_data *data)
{
	int		pid;
	char	**execve_args;

	execve_args = ft_get_execve_args(data);
	if (!execve_args)
	{
		if_execve_args_null(data);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork: Error \n");
		return (free_if_execve_fails(execve_args, NULL));
	}
	ft_execve_helper(data, pid, execve_args);
	free_if_execve_fails(execve_args, data->envp_array);
}
