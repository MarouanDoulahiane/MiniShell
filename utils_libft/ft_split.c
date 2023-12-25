/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:17:55 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/20 05:45:14 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	*ft_fre(char **t, int i)
{
	while (i--)
		free(t[i]);
	free(t);
	return (NULL);
}

static int	ft_count(char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			j++;
		}
		if (j > 0)
		{
			k++;
			j = 0;
		}
	}
	return (k);
}

static int	ft_count2(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_fill(char **t, char *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			t[j] = malloc(sizeof(char) * (ft_count2((char *)s + i, c) + 1));
			if (!t[j])
				return (ft_fre(t, j));
			while (s[i] && s[i] != c)
				t[j][k++] = s[i++];
			t[j++][k] = 0;
			k = 0;
		}
	}
	t[j] = 0;
	return (t);
}

char	**ft_split(char const *s, char c)
{
	char	**t;

	if (!s)
		return (0);
	t = malloc(sizeof(char *) * (ft_count((char *)s, c) + 1));
	if (!t)
		return (0);
	return (ft_fill(t, (char *)s, c));
}
