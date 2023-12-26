/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:43:13 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 15:29:31 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_pwd(t_info *data, t_comd *cmd)
{
	ft_putstr(data->pwd_value, cmd->outp);
	ft_putstr("\n", cmd->outp);
}
