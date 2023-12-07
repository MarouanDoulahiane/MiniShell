/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:12:32 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/07 20:15:39 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

bool	ft_check_valid_key(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] != '=' && str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (true);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	add_back_t_envp(t_envp **envp_list, t_envp *new)
{
	t_envp	*temp;

	if (!envp_list || !new)
		return ;
	if (!*envp_list)
	{
		*envp_list = new;
		return ;
	}
	temp = *envp_list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_append_env(t_data *data, char *str)
{
	char	*key;
	char	*value;

	key = ft_get_key(str);
	value = ft_get_value(str);
	if (ft_get_env(data, key))
	{
		value = ft_strjoin(ft_get_env(data, key), value);
		replace_old_t_env_value(data, key, value);
	}
	else
		add_back_t_envp(&data->envp, create_t_envp(key, value));
	free(key);
}

bool	ft_is_key_exist(t_data *data, char *key)
{
	t_envp	*temp;

	temp = data->envp;
	while (temp)
	{
		if (!ft_strcmp(temp->key, key))
			return (true);
		temp = temp->next;
	}
	return (false);
}

void	ft_add_env(t_data *data, char *str)
{
	char	*key;
	char	*value;

	key = ft_get_key(str);
	value = ft_get_value(str);
	if (ft_is_key_exist(data, key))
		replace_old_t_env_value(data, key, value);
	else
		add_back_t_envp(&data->envp, create_t_envp(key, value));
	free(key);
}
