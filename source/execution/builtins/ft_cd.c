/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:41:54 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/09 19:17:05 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

char	*get_points(char *str)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	temp = NULL;
	while (str[i] && str[i] != '.')
		i++;
	j = i;
	while (str[j] && str[j] == '.')
		j++;
	return (ft_substr(str, i, j - i));
}

bool	ft_cd_home(t_data *data)
{
	if (!data->command[1] || !ft_strcmp(data->command[1], "~"))
	{
		if (chdir(ft_get_env(data, "HOME")) == -1)
		{
			ft_print_err("cd: HOME not set\n");
			return (true);
		}
		if (ft_is_key_exist(data, "OLDPWD"))
			replace_old_t_env_value(data, "OLDPWD", ft_strdup(data->pwd_value));
		free(data->pwd_value);
		data->pwd_value = getcwd(NULL, 0);
		if (ft_is_key_exist(data, "PWD"))
			replace_old_t_env_value(data, "PWD", ft_strdup(data->pwd_value));
		return (true);
	}
	return (false);
}

bool	ft_cd_not_found(t_data *data)
{
	if (chdir(data->command[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", data->command[1]);
		return (true);
	}
	return (false);
}

bool	ft_cd_removed(t_data *data, char *new_path)
{
	char	*temp1;
	char	*temp2;

	if (!new_path)
	{
		ft_print_err("cd: error retrieving current directory:");
		ft_print_err(" getcwd: cannot access parent directories:");
		ft_print_err(" No such file or directory\n");
		new_path = ft_strjoin(ft_get_env(data, "PWD"), "/");
		temp1 = new_path;
		temp2 = get_points(data->command[1]);
		new_path = ft_strjoin(new_path, temp2);
		free(temp1);
		free(temp2);
		if (ft_is_key_exist(data, "OLDPWD"))
			replace_old_t_env_value(data, "OLDPWD", ft_strdup(data->pwd_value));
		free(data->pwd_value);
		data->pwd_value = new_path;
		if (ft_is_key_exist(data, "PWD"))
			replace_old_t_env_value(data, "PWD", ft_strdup(new_path));
		return (true);
	}
	return (false);
}

void	ft_cd(t_data *data)
{
	char	*new_path;

	if (ft_cd_home(data))
		return ;
	if (ft_cd_not_found(data))
		return ;
	new_path = getcwd(NULL, 0);
	if (ft_cd_removed(data, new_path))
		return ;
	if (!ft_strcmp(data->pwd_value, new_path))
	{
		if (ft_is_key_exist(data, "OLDPWD"))
			replace_old_t_env_value(data, "OLDPWD", ft_strdup(data->pwd_value));
		free(new_path);
		return ;
	}
	if (ft_is_key_exist(data, "OLDPWD"))
		replace_old_t_env_value(data, "OLDPWD", ft_strdup(data->pwd_value));
	free(data->pwd_value);
	data->pwd_value = new_path;
	if (ft_is_key_exist(data, "PWD"))
		replace_old_t_env_value(data, "PWD", ft_strdup(new_path));
}
