/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:35:22 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/25 23:30:11 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// void	ft_echo(t_info *data)
// {
// 	int	i;
// 	int	j;
// 	int	n_flag;

// 	i = 1;
// 	n_flag = 1;
// 	while (data->command[i] && data->command[i][0] == '-'
// 		&& data->command[i][1] == 'n')
// 	{
// 		j = 2;
// 		n_flag = 0;
// 		while (data->command[i][j] == 'n')
// 			j++;
// 		if (data->command[i][j] != '\0')
// 			break ;
// 		i++;
// 	}
// 	while (data->command[i])
// 	{
// 		printf("%s", data->command[i]);
// 		if (data->command[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// 	printf("%c", n_flag * '\n');
// }

void	ft_echo(t_comd *cmd)
{
	int	i;
	int	j;
	int	n_flag;

	i = 0;
	n_flag = 1;
	while (cmd->argms[++i] && cmd->argms[i][0] == '-'
		&& cmd->argms[i][1] == 'n')
	{
		j = 2;
		n_flag = 0;
		while (cmd->argms[i][j] == 'n')
			j++;
		if (cmd->argms[i][j] != '\0')
			break ;
	}
	while (cmd->argms[i])
	{
		ft_putstr(cmd->argms[i], cmd->outp);
		if (cmd->argms[i + 1])
			ft_putstr(" ", cmd->outp);
		i++;
	}
	ft_putchar(n_flag * '\n', cmd->outp);
	g_ext_status = 0;
}
