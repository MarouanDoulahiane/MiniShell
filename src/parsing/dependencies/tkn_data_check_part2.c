/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_data_check_part2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:55:16 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/25 03:29:22 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// This function appears to be responsible for checking
// for syntax errors related to quotes in the input line.
// If a syntax error is detected, it sets the global
// exit status and prints an error message before returning a non-zero value.
int	check_syx_quotes_err(char *line)
{
	char	*car;

	if (check_both_quotes(line))
	{
		if (check_both_quotes(line) == 1)
			car = "\"\n";
		else
			car = "'\n";
		g_ext_status = SNTX_ERR;
		ft_putstr("\033[1;31m:(\033[0m Minishell: syntax error near" \
			"unexpected token ", 2);
		ft_putstr(car, 2);
		return (1);
	}
	return (0);
}

int	is_a_directory(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	check_cmd_isdretory(char *str)
{
	DIR		*dir;

	if (str && is_a_directory(str))
	{
		if (!str[1])
		{
			(ft_putstr("\033[1;31m:(\033[0m Minishell: ", 2), \
			(ft_putstr(str, 2)), ft_putstr(" :is a directory\n", 2));
			return (g_ext_status = CMD_EXE_FAILED, 1);
		}
		else
		{
			dir = opendir(str);
			if (dir)
			{
				(ft_putstr("\033[1;31m:(\033[0m Minishell: ", 2), \
				(ft_putstr(str, 2), ft_putstr(" :is a directory\n", 2)));
				if (dir)
					closedir(dir);
				return (g_ext_status = CMD_EXE_FAILED, 1);
			}
		}
	}
	return (0);
}
