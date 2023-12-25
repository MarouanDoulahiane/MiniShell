/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:15:16 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 00:14:55 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// void	ft_export(t_info *data)
// {
// 	int		i;
// 	char	*temp;

// 	i = 1;
// 	while (data->command[i])
// 	{
// 		if (!ft_check_valid_key(data->command[i]))
// 		{
// 			ft_print_err("minishell: export: `");
// 			ft_print_err(data->command[i]);
// 			ft_print_err("': not a valid identifier\n");
// 			i++;
// 			continue ;
// 		}
// 		temp = ft_strchr(data->command[i], '+');
// 		if (temp && temp[1] == '=')
// 			ft_append_env(data, data->command[i]);
// 		else
// 			ft_add_env(data, data->command[i]);
// 		i++;
// 	}
// 	if (!data->command[1])
// 		ft_declare_export(data);
// }

void	ft_export_update_content(t_info *info)
{
	t_envp	*temp;
	char	*temp2;

	temp = info->envp;
	while (temp)
	{
		free(temp->content);
		temp = temp->next;
	}
	temp = info->envp;
	while (temp)
	{
		temp2 = ft_strjoin(ft_strdup(temp->key), "=");
		temp->content = ft_strjoin(temp2, temp->value);
		temp = temp->next;
	}
}

void	ft_export(t_comd *cmd, t_info *info)
{
	int		i;
	char	*temp;

	i = 0;
	while (cmd->argms[++i])
	{
		if (!check_is_valid_arg_for_export(cmd->argms[i]))
		{
			ft_print_err("minishell: export: `", cmd->outp);
			ft_print_err(cmd->argms[i], cmd->outp);
			ft_print_err("': not a valid identifier\n", cmd->outp);
			g_ext_status = 1;
			continue ;
		}
		temp = ft_strchr(cmd->argms[i], '+');
		if (temp && temp[1] == '=')
			ft_append_env(info, cmd->argms[i]);
		else
			ft_add_env(info, cmd->argms[i]);
		ft_export_update_content(info);
	}
	if (!cmd->argms[1])
		ft_declare_export(info, cmd);
	(void)cmd;
	g_ext_status = 0;
}
