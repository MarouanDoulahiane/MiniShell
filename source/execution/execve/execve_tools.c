/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:02:22 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/09 20:22:34 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	**ft_get_path(t_data *data)
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

bool	check_command_if_it_exists_in_path(t_data *data, char **path,
	char **command)
{
	char	*temp;
	int		i;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			return (false);
		*command = ft_strjoin(temp, data->command[0]);
		free(temp);
		if (!*command)
			return (false);
		if (!access(*command, X_OK))
			return (true);
		free(*command);
		i++;
	}
	return (false);
}

bool	check_command_if_it_exists_in_current_dir(t_data *data, char **command)
{
	if (data->command[0][0] != '.' || data->command[0][1] != '/')
		return (false);
	*command = ft_strdup(data->command[0]);
	if (!*command)
		return (false);
	if (!access(*command + 2, X_OK))
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

char	**ft_get_execve_args(t_data *data)
{
	char		**execve_args;
	char		*command;
	char		**path;
	int			i;

	command = NULL;
	path = ft_get_path(data);
	if (!path)
		return (NULL);
	i = 0;
	if (!check_command_if_it_exists_in_current_dir(data, &command))
		if (!check_command_if_it_exists_in_path(data, path, &command))
			return (free_array(path), NULL);
	execve_args = malloc(sizeof(char *) * (ft_array_len(data->command) + 1));
	if (!execve_args)
		return (free_array(path), NULL);
	execve_args[0] = command;
	i = 1;
	while (data->command[i])
	{
		execve_args[i] = data->command[i];
		i++;
	}
	return (execve_args[i] = NULL, free_array(path), execve_args);
}
