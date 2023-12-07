/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:24:23 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/07 20:16:50 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	ft_exit_helper(t_data	*data)
{
	if (ft_cmd_isdigit(data->command[1]))
		printf("exit\nminishell: exit: too many arguments\n");
	else
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n",
			data->command[1]);
		exit(255);
	}
}

void	ft_exit(t_data	*data)
{
	int	i;

	i = 0;
	while (data->command[i])
		i++;
	if (i == 1)
		exit(0);
	else if (i == 2)
	{
		if (ft_cmd_isdigit(data->command[1]))
		{
			printf("exit\n");
			free_t_data(data);
			exit(ft_atoi(data->command[1]));
		}
		else
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n",
				data->command[1]);
			exit(255);
		}
	}
	else
		ft_exit_helper(data);
}
