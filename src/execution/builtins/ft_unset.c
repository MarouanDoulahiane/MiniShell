/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:26:21 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 02:11:10 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

// bool	ft_unset_helper(t_info *data, t_envp *temp, t_envp *prev, char *command)
// {
// 	if (ft_strcmp(temp->key, "_") && !ft_strcmp(temp->key, command))
// 	{
// 		if (!ft_strcmp(temp->key, "PATH"))
// 			data->allowed_path = false;
// 		if (prev)
// 			prev->next = temp->next;
// 		else
// 			data->envp = temp->next;
// 		free(temp->key);
// 		free(temp->value);
// 		free(temp);
// 		return (true);
// 	}
// 	return (false);
// }

bool	ft_unset_h(t_info *data, t_envp *temp, t_envp *prev, t_comd *cmd)
{
	if (ft_strcmp(temp->key, "_") && !ft_strcmp(temp->key, cmd->argms[1]))
	{
		if (!ft_strcmp(temp->key, "PATH"))
			data->allowed_path = false;
		if (prev)
			prev->next = temp->next;
		else
			data->envp = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp->content);
		free(temp);
		return (true);
	}
	return (false);
}

// void	unset_path(t_info *data, char *command, t_envp **prev)
// {
// 	if (!ft_strcmp(command, "PATH"))
// 		data->allowed_path = false;
// 	*prev = NULL;
// }

void	unset_path(t_info *data, t_comd *cmd, t_envp **prev)
{
	if (!ft_strcmp(cmd->argms[1], "PATH"))
		data->allowed_path = false;
	*prev = NULL;
}

// void	ft_unset(t_info	*data)
// {
// 	int		i;
// 	t_envp	*temp;
// 	t_envp	*prev;

// 	i = 0;
// 	while (data->command[++i])
// 	{
// 		if (!check_is_valid_unset_identifier(data->command[i]))
// 		{
// 			ft_print_err("minishell: unset: `");
// 			ft_print_err(data->command[i]);
// 			ft_print_err("': not a valid identifier\n");
// 			continue ;
// 		}
// 		unset_path(data, data->command[i], &prev);
// 		temp = data->envp;
// 		while (temp)
// 		{
// 			if (ft_unset_helper(data, temp, prev,
// 					data->command[i]))
// 				break ;
// 			prev = temp;
// 			temp = temp->next;
// 		}
// 	}
// }

void	ft_unset(t_comd *cmd, t_info *info)
{
	int		i;
	t_envp	*temp;
	t_envp	*prev;

	i = 0;
	while (cmd->argms[++i])
	{
		if (!check_is_valid_unset_identifier(cmd->argms[i]))
		{
			ft_print_err("minishell: unset: `", cmd->outp);
			ft_print_err(cmd->argms[i], cmd->outp);
			ft_print_err("': not a valid identifier\n", cmd->outp);
			g_ext_status = 1;
			continue ;
		}
		unset_path(info, cmd, &prev);
		temp = info->envp;
		while (temp)
		{
			if (ft_unset_h(info, temp, prev, cmd))
				break ;
			prev = temp;
			temp = temp->next;
		}
	}
}
