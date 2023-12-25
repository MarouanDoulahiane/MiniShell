/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 18:27:43 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 00:20:38 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	execute_builtins(t_comd *cmd, t_info *info)
{
	if (!ft_strcmp(cmd->argms[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->argms[0], "env"))
		ft_env(cmd, info);
	else if (!ft_strcmp(cmd->argms[0], "cd"))
		ft_cd(cmd, info);
	else if (!ft_strcmp(cmd->argms[0], "pwd"))
		ft_pwd(info, cmd);
	else if (!ft_strcmp(cmd->argms[0], "export"))
		ft_export(cmd, info);
	else if (!ft_strcmp(cmd->argms[0], "unset"))
		ft_unset(cmd, info);
	else if (!ft_strcmp(cmd->argms[0], "exit"))
		ft_exit(cmd);
}

// void	final_execute(t_comd *cmd, t_info *info)
// {
// 	if (cmd->inp == -1 || cmd->outp == -1)
// 		return ;
// 	if (are_builin(cmd))
// 		execute_builtins(cmd, info);
// 	else
// 		ft_execve(cmd, info);
// }
