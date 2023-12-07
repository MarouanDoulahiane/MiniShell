/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:15:16 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/07 14:23:47 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/execution.h"

void	ft_export(t_data *data)
{
	int		i;
	char	*temp;

	i = 1;
	while (data->command[i])
	{
		if (!ft_check_valid_key(data->command[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				data->command[i]);
			i++;
			continue ;
		}
		temp = ft_strchr(data->command[i], '+');
		if (temp && temp[1] == '=')
			ft_append_env(data, data->command[i]);
		else
			ft_add_env(data, data->command[i]);
		i++;
	}
	if (!data->command[1])
		ft_declare_export(data);
}
