/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:35:22 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/09 19:12:58 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	ft_echo(t_data *data)
{
	int	i;
	int	j;
	int	n_flag;

	i = 1;
	n_flag = 1;
	while (data->command[i] && data->command[i][0] == '-'
		&& data->command[i][1] == 'n')
	{
		j = 2;
		n_flag = 0;
		while (data->command[i][j] == 'n')
			j++;
		if (data->command[i][j] != '\0')
			break ;
		i++;
	}
	while (data->command[i])
	{
		printf("%s", data->command[i]);
		if (data->command[i + 1])
			printf(" ");
		i++;
	}
	printf("%c", n_flag * '\n');
}
