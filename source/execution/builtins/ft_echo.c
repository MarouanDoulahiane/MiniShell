/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:35:22 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/07 17:35:00 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/execution.h"

void	ft_echo(t_data *data)
{
	int	i;
	int	j;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (data->command[i] && data->command[i][0] == '-'
		&& data->command[i][1] == 'n' && data->command[i][j])
	{
		j = 2;
		n_flag = 1;
		while (data->command[i][j] == 'n')
			j++;
		i++;
	}
	while (data->command[i])
	{
		printf("%s", data->command[i]);
		if (data->command[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}
