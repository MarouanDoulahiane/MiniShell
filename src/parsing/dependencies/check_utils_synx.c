/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils_synx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 02:09:07 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/20 05:53:56 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	check_sin_quotes(char *cmd, int *i, int *check)
{
	while (cmd[*i])
	{
		if (cmd[*i] == '\'' && *check == 0)
			*check = 2;
		else if (cmd[*i] == '\'' && *check == 2)
		{
			*check = 0;
			break ;
		}
		(*i)++;
	}
}

int	is_val_char(int c)
{
	if (c && (ft_isalnum(c) || c == '$' || c == '_' || c == '?'))
		return (1);
	return (0);
}

int	check_quotes(char *cmd, int idx)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (cmd[i] && i != idx)
	{
		if (check == 0 && cmd[i] == '\"')
			check = 1;
		else if (check == 1 && cmd[i] == '\"')
			check = 0;
		else if (check == 0 && cmd[i] == '\'')
			check = 2;
		else if (check == 2 && cmd[i] == '\'')
			check = 0;
		i++;
	}
	return (check);
}

int	check_red_pipe(char c, char *cmd, int idx)
{
	if (check_quotes(cmd, idx))
		return (0);
	if (c && (c == '|' || c == ' ' || c == '<' || c == '>'))
		return (1);
	return (0);
}

// It checks for both double and single quotes
//and uses the checker variable to keep track of the quote status.
int	check_both_quotes(char *cmd)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\"' && check == 0)
		{
			while (cmd[i])
			{
				if (cmd[i] == '\"' && check == 0)
					check = 1;
				else if (cmd[i] == '\"' && check == 1)
				{
					check = 0;
					break ;
				}
				i++;
			}
		}
		else if (cmd[i] == '\'' && check == 0)
			check_sin_quotes(cmd, &i, &check);
	}
	return (check);
}
