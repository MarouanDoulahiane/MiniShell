/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_envp_getters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:12:29 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/07 13:34:13 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/execution.h"

char	*ft_get_key(char *str)
{
	char	*key;
	char	*temp;

	temp = ft_strchr(str, '+');
	if (!temp)
		temp = ft_strchr(str, '=');
	key = ft_substr(str, 0, temp - str);
	return (key);
}

char	*ft_get_value(char *str)
{
	char	*value;
	char	*temp;

	temp = ft_strchr(str, '=');
	if (!temp)
		return (NULL);
	value = ft_substr(temp + 1, 0, ft_strlen(temp + 1));
	return (value);
}

char	*ft_get_env(t_data *data, char *key)
{
	t_envp	*temp;

	temp = data->envp;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}