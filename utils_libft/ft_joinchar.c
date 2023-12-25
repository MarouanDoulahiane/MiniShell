/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 01:44:34 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/20 05:51:48 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_joinchar(char *str, char c)
{
	char	*str2;
	int		i;

	i = 0;
	str2 = (char *)malloc(ft_strlen(str) + 2);
	while (str[i])
	{
		str2[i] = str[i];
		i++;
	}
	str2[i++] = c;
	str2[i] = 0;
	free(str);
	return (str2);
}
