/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:31:32 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/26 00:28:09 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
// In summary, the ft_getchar function is responsible
// for appending characters to the string pointed to by
//  *str based on certain conditions related to single quotes,
//   double quotes, and the result of the ft_quotes function. It's
//    a part of a larger process where characters are being processed
//     based on specific criteria related to quotes.
void	append_char_str(char *val, char **str, int i)
{
	if (val[i] != '\'' && val[i] != '\"')
		*str = ft_joinchar(*str, val[i]);
	if (val[i] == '\'' && check_quotes(val, i) == 1)
		*str = ft_joinchar(*str, val[i]);
	if (val[i] == '\"' && check_quotes(val, i) == 2)
		*str = ft_joinchar(*str, val[i]);
}

char	*if_contain_env_var(char *str, t_context *context)
{
	t_envp		*ptr;
	int			len;
	char		*copy;

	ptr = context->data->env;
	len = ft_strlen(str);
	while (ptr && str[0])
	{
		copy = ptr->content;
		if (copy[len] && !ft_strncmp(copy, str, len)
			&& copy[len] == '=' && copy[len + 1])
			return (ft_strdup(copy + len + 1));
		ptr = ptr->next;
	}
	return (ft_strdup(""));
}
// function extracts a variable name
// from the input string, searches for its
//  value using the <if_contain_env_var> function,
//   and returns the value. It handles cases
//   where the variable is not in quotes and is
//   followed by alphanumeric characters or underscores.

char	*extract_value_checkname(char *val, int	*idx, t_context *context)
{
	char	*ptr;
	char	*str;
	int		i;

	str = ft_strdup("");
	i = *idx;
	if (!check_quotes(val, i + 2) && !ft_isalnum(val[i + 1])
		&& val[i + 1] != '?' && val[i + 1] != '_')
	{
		while (val[i] && val[i] != '$')
			str = ft_joinchar(str, val[i++]);
		if (val[i] == '$')
			str = ft_joinchar(str, val[i++]);
	}
	while (val[++i] && (ft_isalnum(val[i]) || val[i] == '_'))
		str = ft_joinchar(str, val[i]);
	i--;
	*idx = i;
	ptr = if_contain_env_var(str, context);
	free(str);
	return (ptr);
}

void	get_val_concat(char	*val, int *i, char **str, t_context *context)
{
	char	*tmp;

	context->data->flg = 1;
	if (val[*i + 1] == '?')
	{
		(*i)++;
		tmp = ft_itoa(g_ext_status);
	}
	else
		tmp = extract_value_checkname(val, i, context);
	*str = ft_strjoin(*str, tmp);
	free (tmp);
}
// In summary, this function generates a unique filename for a temporary file
//  by appending a number to a fixed prefix ("/tmp/hd_"). It iterates
//  and increments the number until it finds a filename that does not exist
//  in the "/tmp" directory, and then it returns that unique filename.

char	*expand_delim(char *delim)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (delim[i])
	{
		append_char_str(delim, &str, i);
		i++;
	}
	return (str);
}
