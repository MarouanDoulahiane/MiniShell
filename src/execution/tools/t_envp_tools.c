/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:12:32 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 02:51:01 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	check_is_valid_arg_for_export(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i] && str[i] != '=' && (str[i] != '+' && str[i + 1] != '='))
	{
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

void	ft_append_env(t_info *data, char *str)
{
	char	*key;
	char	*value;
	char	*temp;
	char	*temp2;

	key = ft_get_key(str);
	value = ft_get_value(str);
	temp2 = ft_get_env(data, key);
	if (temp2)
	{
		temp = value;
		value = ft_strjoin(ft_strdup(temp2), value);
		free(temp);
		temp = NULL;
		replace_old_t_env_value(data, key, value);
	}
	else
	{
		add_back_t_envp(&data->envp, create_t_envp(key, value));
		free(value);
	}
	free(key);
}

bool	ft_is_key_exist(t_info *data, char *key)
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

void	ft_add_env(t_info *data, char *str)
{
	char	*key;
	char	*value;

	key = ft_get_key(str);
	value = ft_get_value(str);
	if (ft_is_key_exist(data, key))
		replace_old_t_env_value(data, key, value);
	else
	{
		add_back_t_envp(&data->envp, create_t_envp(key, value));
		free(value);
	}
	free(key);
}
