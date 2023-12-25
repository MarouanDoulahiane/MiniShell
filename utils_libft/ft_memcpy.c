/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:09:21 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/03 18:11:14 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dt;
	unsigned char	*sc;

	if (!dst && !src)
		return (0);
	i = 0;
	dt = (unsigned char *)dst;
	sc = (unsigned char *)src;
	while (i < n)
	{
		dt[i] = sc[i];
		i++;
	}
	return (dst);
}
