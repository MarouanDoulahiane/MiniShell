/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 01:17:29 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/17 01:17:35 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	cmd_to_str_add(t_tkn **data, char *cmd, int *idx)
{
	char	*ptr;
	int		i;

	i = (*idx);
	ptr = ft_strdup("");
	while (cmd[i] && !check_red_pipe(cmd[i], cmd, i))
	{
		ptr = ft_joinchar(ptr, cmd[i]);
		if ((cmd[i + 1] && is_red_char(cmd[i + 1]) && !check_quotes(cmd, i + 1))
			|| !cmd[i + 1] || (cmd[i + 1] == ' ' && !check_quotes(cmd, i +1)))
		{
			ft_add_tkn_back(data, ft_new_tkn(ptr));
			break ;
		}
		i++;
	}
	(*idx) = i;
}

int	is_red_char(char c)
{
	if (c && (c == '|' || c == '>' || c == '<' || c == ' '))
		return (1);
	return (0);
}

void	add_operator_tkn(t_tkn **data, char *cmd, int *idx)
{
	char	*ptr;
	int		i;

	i = (*idx);
	ptr = ft_strdup("");
	while (cmd[i] && check_red_pipe(cmd[i], cmd, i) && cmd[i] != ' ')
	{
		ptr = ft_joinchar(ptr, cmd[i]);
		if (!ft_strncmp(ptr, "<<", 2) || !ft_strncmp(ptr, ">>", 2)
			|| (!ft_strncmp(ptr, "<", 1) && cmd[i + 1] != '<')
			|| (!ft_strncmp(ptr, ">", 1) && cmd[i + 1] != '>')
			|| !ft_strncmp(ptr, "|", 1))
		{
			ft_add_tkn_back(data, ft_new_tkn(ptr));
			break ;
		}
		i++;
	}
	(*idx) = i;
}
