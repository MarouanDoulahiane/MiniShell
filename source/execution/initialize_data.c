/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:04:46 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/07 17:32:28 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/execution.h"

t_envp	*create_t_envp(char *key, char *value)
{
	t_envp	*new;

	new = (t_envp *)malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->is_envp = true;
	new->key = ft_strdup(key);
	if (!value)
		new->value = NULL;
	else
		new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

t_envp	*initialize_t_envp_witoout_envp(void)
{
	t_envp	*envp_list;
	char	pwdbuf[1024];
	char	*temp;

	envp_list = NULL;
	getcwd(pwdbuf, sizeof(pwdbuf));
	add_back_t_envp(&envp_list, create_t_envp("SHLVL", "1"));
	add_back_t_envp(&envp_list, create_t_envp("PWD", pwdbuf));
	add_back_t_envp(&envp_list, create_t_envp("OLDPWD", NULL));
	temp = ft_strjoin(pwdbuf, "/./minishell");
	add_back_t_envp(&envp_list, create_t_envp("_", temp));
	free(temp);
	return (envp_list);
}

t_envp	*initialize_t_envp(char **envp)
{
	t_envp	*envp_list;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	envp_list = NULL;
	if (!*envp)
		return (initialize_t_envp_witoout_envp());
	while (envp[i])
	{
		key = ft_substr(envp[i], 0, ft_strchr(envp[i], '=') - envp[i]);
		value = ft_strchr(envp[i], '=') + 1;
		add_back_t_envp(&envp_list, create_t_envp(key, value));
		free(key);
		i++;
	}
	return (envp_list);
}

t_data	*initialize_data(char **envp)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->input = NULL;
	data->command = NULL;
	data->envp_array = NULL;
	data->envp = NULL;
	data->envp = initialize_t_envp(envp);
	if (!data->envp)
	{
		free(data);
		return (NULL);
	}
	printf("try to find a bug in init data\n");
	return (data);
}
