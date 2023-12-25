/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:21:36 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/15 18:28:22 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_realloc(char **tab, char *str)
{
	char	**out;
	int		i;

	i = 0;
	while (tab && tab[i])
		i++;
	out = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tab && tab[i])
	{
		out[i] = ft_calloc(sizeof(char), 1);
		out[i] = ft_strjoin(out[i], tab[i]);
		i++;
	}
	out[i] = ft_calloc(sizeof(char), 1);
	out[i] = ft_strjoin(out[i], str);
	i++;
	out[i] = NULL;
	free_tab(tab);
	return (out);
}
