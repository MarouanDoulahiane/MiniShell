/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:31:11 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/15 18:33:14 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_calloc(size_t nbr, size_t size)
{
	void	*str;
	size_t	len;

	len = nbr * size;
	str = (void *)malloc(len);
	if (!str)
		return (NULL);
	ft_bzero(str, len);
	return (str);
}
