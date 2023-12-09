/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:26:21 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/09 19:43:47 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

bool	check_is_valid_unset_identifier(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	ft_unset_helper(t_data *data, t_envp *temp, t_envp *prev)
{
	if (ft_strcmp(temp->key, "_"))
	{
		if (prev)
			prev->next = temp->next;
		else
			data->envp = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		return (true);
	}
}

void	ft_unset(t_data	*data)
{
	int		i;
	t_envp	*temp;
	t_envp	*prev;

	i = 0;
	while (data->command[++i])
	{
		if (!check_is_valid_unset_identifier(data->command[i]))
		{
			ft_print_err("minishell: unset: `");
			ft_print_err(data->command[i]);
			ft_print_err("': not a valid identifier\n");
			continue ;
		}
		temp = data->envp;
		prev = NULL;
		while (temp)
		{
			if (!ft_strcmp(temp->key, data->command[i])
				&& ft_unset_helper(data, temp, prev))
				break ;
			prev = temp;
			temp = temp->next;
		}
	}
}
