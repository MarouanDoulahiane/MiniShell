/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:04:46 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/09 20:07:13 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_envp	*create_t_envp(char *key, char *value)
{
	t_envp	*new;

	new = (t_envp *)malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->is_envp = true;
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	if (!value)
		new->value = NULL;
	else
		new->value = ft_strdup(value);
	if (value && !new->value)
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_envp	*initialize_t_envp_witoout_envp(void)
{
	t_envp	*envp_list;
	char	*temp;
	char	buf[1024];

	envp_list = NULL;
	getcwd(buf, 1024);
	add_back_t_envp(&envp_list, create_t_envp("SHLVL", "1"));
	add_back_t_envp(&envp_list, create_t_envp("PWD", buf));
	add_back_t_envp(&envp_list, create_t_envp("OLDPWD", NULL));
	temp = ft_strjoin(buf, "/./minishell");
	if (!temp)
	{
		free_t_envp(envp_list);
		return (NULL);
	}
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
		if (!key)
		{
			free_t_envp(envp_list);
			return (NULL);
		}
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
	char	buf[1024];

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->envp_array = NULL;
	data->command = NULL;
	data->input = NULL;
	data->allowed_path = true;
	data->envp = initialize_t_envp(envp);
	if (!data->envp)
		return (free(data), NULL);
	getcwd(buf, 1024);
	data->pwd_key = ft_strdup("PWD");
	data->pwd_value = ft_strdup(buf);
	printf("pwd_value: %s\n", data->pwd_value);
	if (!data->pwd_key || !data->pwd_value)
	{
		free_t_data(data);
		return (NULL);
	}
	return (data);
}
