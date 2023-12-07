/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:21:25 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/07 12:41:55 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/execution.h"

void	free_t_envp(t_envp	*envp)
{
	t_envp	*temp;

	while (envp)
	{
		temp = envp;
		envp = envp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_t_data(t_data	*data)
{
	free_t_envp(data->envp);
	free_array(data->envp_array);
	free_array(data->command);
	free(data->input);
	free(data);
}
