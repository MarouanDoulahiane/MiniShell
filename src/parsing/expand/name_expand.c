/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:47:51 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/26 02:54:58 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_quotes_exist(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

//  It iterates through the string and counts the number of sequences of
// non-space characters separated by spaces or tabs.
int	cont_no_wspace(char *str)
{
	int	i;
	int	x;
	int	flg;

	i = 0;
	x = 0;
	flg = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((str[i] != '\t' && str[i] != ' ') && flg == 0)
		{
			x++;
			flg = 1;
		}
		if ((str[i] == '\t' || str[i] == ' '))
			flg = 0;
		i++;
	}
	return (x);
}
// function that expands variables in a string

char	*expand_var_str(char *val, t_context *context)
{
	char	*str;
	int		i;

	context->data->flg = 0;
	i = 0;
	str = ft_strdup("");
	while (val[i])
	{
		if (val[i] == '$' && is_val_char(val[i + 1])
			&& (check_quotes(val, i) == 0 || check_quotes(val, i) == 1))
		{
			if (val[i + 1] != '$' && !ft_isdigit(val[i + 1]))
				get_val_concat(val, &i, &str, context);
			else
				i++;
		}
		else
			append_char_str(val, &str, i);
		i++;
	}
	if (context->data->flg && (!str[0] || cont_no_wspace(str) > 1))
		return (free(val), free(str), ft_strdup("\b"));
	return (free(val), str);
}
