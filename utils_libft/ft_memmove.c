/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:57:11 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/03 18:09:28 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*dt;
	unsigned char	*sc;

	if (!dst && !src)
		return (NULL);
	dt = (unsigned char *)dst;
	sc = (unsigned char *)src;
	if (dt > sc)
	{
		while (n-- > 0)
			dt[n] = sc[n];
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
