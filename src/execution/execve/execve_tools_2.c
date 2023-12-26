/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_tools_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:07:44 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/26 02:50:35 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_t_envp_size(t_envp *envp)
{
	int	i;

	i = 0;
	while (envp)
	{
		i++;
		envp = envp->next;
	}
	return (i);
}

void	ft_env_to_array_helper(char **envp_array, t_envp *envp, int i)
{
	envp_array[i] = NULL;
	if (envp->value)
		envp_array[i] = ft_strjoin(ft_strdup(envp->key), "=");
}

char	**ft_env_to_array(t_envp *envp)
{
	char		**envp_array;
	char		*temp;
	int			i;

	envp_array = malloc(sizeof(char *) * (ft_t_envp_size(envp) + 1));
	if (!envp_array)
		return (NULL);
	i = 0;
	while (envp)
	{
		ft_env_to_array_helper(envp_array, envp, i);
		if (!envp_array[i])
			return (free_array(envp_array), NULL);
		if (envp->value)
		{
			temp = envp_array[i];
			envp_array[i] = ft_strjoin(ft_strdup(envp_array[i]), envp->value);
			free(temp);
			if (!envp_array[i])
				return (free_array(envp_array), NULL);
		}
		i++;
		envp = envp->next;
	}
	return (envp_array[i] = NULL, envp_array);
}

		// envp_array[i] = NULL;
		// if (envp->value)
		// 	envp_array[i] = ft_strjoin(ft_strdup(envp->key), "=");