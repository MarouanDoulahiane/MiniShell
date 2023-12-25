/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:28:58 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/25 23:29:52 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// void	ft_env(t_info *data)
// {
// 	t_envp	*temp;

// 	temp = data->envp;
// 	while (temp)
// 	{
// 		if (temp->value)
// 			printf("%s=%s\n", temp->key, temp->value);
// 		temp = temp->next;
// 	}
// }

void	ft_env(t_comd *cmd, t_info *info)
{
	t_envp	*temp;

	temp = info->envp;
	while (temp)
	{
		if (temp->value)
		{
			ft_putstr(temp->key, cmd->outp);
			ft_putstr("=", cmd->outp);
			ft_putstr(temp->value, cmd->outp);
			ft_putstr("\n", cmd->outp);
		}
		temp = temp->next;
	}
	(void)cmd;
	g_ext_status = 0;
}
