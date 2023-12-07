/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:43:13 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/07 20:16:54 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	ft_pwd(void)
{
	char	pwdbuf[1024];

	getcwd(pwdbuf, sizeof(pwdbuf));
	printf("%s\n", pwdbuf);
}
