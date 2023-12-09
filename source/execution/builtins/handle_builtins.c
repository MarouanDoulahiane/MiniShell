/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:26:54 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/09 18:32:35 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	handle_builtins(t_data *data)
{
	if (ft_strcmp(data->command[0], "echo") == 0)
		ft_echo(data);
	else if (ft_strcmp(data->command[0], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(data->command[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(data->command[0], "export") == 0)
		ft_export(data);
	else if (ft_strcmp(data->command[0], "unset") == 0)
		ft_unset(data);
	else if (ft_strcmp(data->command[0], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(data->command[0], "exit") == 0)
		ft_exit(data);
	else
		ft_execve(data);
}
