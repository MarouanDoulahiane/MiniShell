/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_old_t_env_value.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:39:57 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/06 19:39:58 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/execution.h"

void	replace_old_t_env_value(t_data *data, char *key, char *value)
{
	t_envp	*temp;

	temp = data->envp;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = value;
			return ;
		}
		temp = temp->next;
	}
}
