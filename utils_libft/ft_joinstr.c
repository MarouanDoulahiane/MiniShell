/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:16:12 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/13 11:23:05 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	int		len;
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	len = s1_len + s2_len;
	join = (char *)malloc(sizeof(char) * len + 1);
	if (!join)
		return (NULL);
	ft_memcpy(join, s1, s1_len);
	ft_memcpy(join + s1_len, s2, s2_len);
	join[len] = '\0';
	free (s1);
	return (join);
}
