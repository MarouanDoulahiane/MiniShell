/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:11:27 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/24 01:52:03 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// function processes token values, updates the arguments of a t_cmd structure
//based on certain conditions, and then triggers further command processing.
void	expand_check_update_cmdargs(t_tkn *ptr, t_comd *new_c)
{
	int		i;
	char	**trim;

	i = -1;
	if (ptr->flg && ft_strchr(ptr->val, ' '))
	{
		trim = ft_split(ptr->val, ' ');
		while (trim[++i])
			new_c->argms = ft_realloc(new_c->argms, trim[i]);
		free_tab(trim);
	}
	else if (ft_strlen(ptr->val))
		new_c->argms = ft_realloc(new_c->argms, ptr->val);
	if (new_c->argms)
		check_update_cmd(&new_c);
}

// function processes each character in the value array, expanding
// variables and characters based on specific conditions, and finally
//  returns the expanded string after freeing the original value.
char	*expand_var_char(char *val, t_context *context)
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
	return (free(val), str);
}
