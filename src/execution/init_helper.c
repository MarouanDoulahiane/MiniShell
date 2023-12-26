/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 02:20:38 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 02:21:07 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tkn	*init(t_context *context)
{
	t_tkn	*data;

	if (!context)
		exit(1);
	data = malloc(sizeof(t_tkn *));
	if (!data)
		exit(1);
	return (data);
}
