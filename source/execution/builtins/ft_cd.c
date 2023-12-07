/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:41:54 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/07 17:33:45 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/execution.h"

bool	check_if_dir_exist(char *path)
{
	char	*temp;

	if (!ft_strcmp(path, "."))
	{
		temp = getcwd(NULL, 0);
		if (!temp)
		{
			printf("cd: error retrieving current directory: getcwd: cannot ");
			printf("access parent directories: No such file or directory\n");
			return (false);
		}
		else
			free(temp);
	}
	return (true);
}

void	ft_cd(t_data *data)
{
	if (!check_if_dir_exist(data->command[1]))
		return ;
	if (data->command[1])
	{
		if (chdir(data->command[1]) == -1)
		{
			printf("cd: %s: No such file or directory\n", data->command[1]);
			return ;
		}
		else
			replace_old_t_env_value(data, "OLDPWD",
				ft_strdup(ft_get_env(data, "PWD")));
	}
	else
	{
		if (chdir(getenv("HOME")) == -1)
		{
			printf("cd: HOME not set\n");
			return ;
		}
		else
			replace_old_t_env_value(data, "OLDPWD",
				ft_strdup(ft_get_env(data, "PWD")));
	}
	replace_old_t_env_value(data, "PWD", getcwd(NULL, 0));
}
