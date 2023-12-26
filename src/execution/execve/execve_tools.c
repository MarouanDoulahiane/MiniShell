/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:02:22 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 15:36:19 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**ft_get_path(t_info *data)
{
	char	**path;

	path = ft_split(ft_get_env(data, "PATH"), ':');
	if (!path && data->allowed_path)
	{
		path = ft_split("usr/gnu/bin:/usr/local/bin:/bin:/usr/bin",
				':');
		if (!path)
			return (NULL);
	}
	return (path);
}

bool	check_command_if_it_exists_in_path(t_comd *cmd,
	char **path, char **command)
{
	char	*temp;
	int		i;

	i = 0;
	while (path[i])
	{
		if (cmd->comd[0] == '/' || cmd->comd[0] == '.')
			break ;
		temp = ft_strjoin(ft_strdup(path[i]), "/");
		if (!temp)
			return (false);
		*command = ft_strjoin(temp, cmd->comd);
		if (!*command)
			return (false);
		if (!access(*command, X_OK))
			return (true);
		free(*command);
		i++;
	}
	return (false);
}

bool	check_command_if_it_exists_in_current_dir(t_comd *cmd, char **command)
{
	if ((cmd->comd[0] != '.' && cmd->comd[1] != '/' && cmd->comd[0] != '/'))
		return (false);
	*command = ft_strdup(cmd->comd);
	if (!*command)
		return (false);
	if (!access(*command, X_OK))
		return (true);
	free(*command);
	return (false);
}

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**ft_get_execve_args(t_comd *cmd, t_info *data)
{
	char	**execve_args;
	char	*command;
	char	**path;
	int		i;

	command = NULL;
	path = ft_get_path(data);
	if (!path)
		return (NULL);
	i = 0;
	if (!check_command_if_it_exists_in_current_dir(cmd, &command))
		if (!check_command_if_it_exists_in_path(cmd, path, &command))
			return (free_array(path), NULL);
	execve_args = malloc(sizeof(char *) * (ft_array_len(cmd->argms) + 1));
	if (!execve_args)
		return (free_array(path), NULL);
	execve_args[0] = command;
	i = 1;
	while (cmd->argms[i])
	{
		execve_args[i] = cmd->argms[i];
		i++;
	}
	return (execve_args[i] = NULL, free_array(path), execve_args);
}
