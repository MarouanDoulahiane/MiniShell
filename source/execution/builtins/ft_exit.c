/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:24:23 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/09 20:57:03 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	ft_exit_helper(t_data	*data)
{
	if (ft_cmd_isdigit(data->command[1]))
	{
		ft_print_err("exit\n");
		ft_print_err("minishell: exit: too many arguments\n");
	}
	else
	{
		ft_print_err("exit\nminishell: exit: ");
		ft_print_err(data->command[1]);
		ft_print_err(": numeric argument required\n");
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
			ft_print_err("exit\nminishell: exit: ");
			ft_print_err(data->command[1]);
			ft_print_err(": numeric argument required\n");
			exit(255);
		}
	}
	else
		ft_exit_helper(data);
}
