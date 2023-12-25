/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:45:31 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/20 05:49:41 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_nb(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
	{
		i++;
		nb *= -1;
	}
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nbr)
{
	char	*out;
	long	nb;
	int		i;

	nb = nbr;
	i = count_nb(nb);
	out = malloc(nb);
	if (!out)
		return (NULL);
	if (nb < 0)
	{
		out[0] = '-';
		nb *= -1;
	}
	out[i] = '\0';
	while (i && (nb != 0 || nbr == 0))
	{
		out[--i] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (out);
}
