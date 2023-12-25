/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:24:23 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/25 23:28:40 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// void	ft_exit_helper(t_info	*data)
// {
// 	if (ft_cmd_isdigit(data->command[1]))
// 	{
// 		ft_print_err("exit\n");
// 		ft_print_err("minishell: exit: too many arguments\n");
// 	}
// 	else
// 	{
// 		ft_print_err("exit\nminishell: exit: ");
// 		ft_print_err(data->command[1]);
// 		ft_print_err(": numeric argument required\n");
// 		exit(255);
// 	}
// }

// void	ft_exit(t_info	*data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->command[i])
// 		i++;
// 	if (i == 1)
// 		exit(0);
// 	else if (i == 2)
// 	{
// 		if (ft_cmd_isdigit(data->command[1]))
// 		{
// 			printf("exit\n");
// 			exit(ft_atoi(data->command[1]));
// 		}
// 		else
// 		{
// 			ft_print_err("exit\nminishell: exit: ");
// 			ft_print_err(data->command[1]);
// 			ft_print_err(": numeric argument required\n");
// 			exit(255);
// 		}
// 	}
// 	else
// 		ft_exit_helper(data);
// }

void	ft_exit_helper(t_comd *cmd)
{
	if (ft_cmd_isdigit(cmd->argms[1]))
	{
		ft_print_err("exit\n", cmd->outp);
		ft_print_err("minishell: exit: too many arguments\n", cmd->outp);
		g_ext_status = 1;
	}
	else
	{
		ft_print_err("exit\nminishell: exit: ", cmd->outp);
		ft_print_err(cmd->argms[1], cmd->outp);
		ft_print_err(": numeric argument required\n", cmd->outp);
		exit(255);
	}
}

void	ft_exit(t_comd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argms[i])
		i++;
	if (i == 1)
		exit(0);
	else if (i == 2)
	{
		if (ft_cmd_isdigit(cmd->argms[1]))
		{
			ft_putstr("exit\n", cmd->outp);
			exit(ft_atoi(cmd->argms[1]));
		}
		else
		{
			ft_print_err("exit\nminishell: exit: ", cmd->outp);
			ft_print_err(cmd->argms[1], cmd->outp);
			ft_print_err(": numeric argument required\n", cmd->outp);
			exit(255);
		}
	}
	else
		ft_exit_helper(cmd);
}
