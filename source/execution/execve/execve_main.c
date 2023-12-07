#include "../../../headers/execution.h"

typedef struct s_garbage
{
	void	*address;
	struct s_garbage	*next;
}	t_garbage;

void	ft_add_garbage(t_garbage **garbage, void *address)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return ;
	new->address = address;
	new->next = *garbage;
	*garbage = new;
}

void	ft_free_garbage(t_garbage **garbage, char **array)
{
	t_garbage	*tmp;

	while (*garbage)
	{
		tmp = *garbage;
		*garbage = (*garbage)->next;
		free(tmp->address);
		free(tmp);
	}
	free_array(array);
}

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**ft_get_execve_args(t_data *data)
{
	t_garbage	*garbage;
	char		**execve_args;
	char		*command;
	char		**path;
	int			i;

	command = NULL;
	path = ft_split(ft_get_env(data, "PATH"), ':');
	if (path == NULL)
	{
		path = ft_split("usr/gnu/bin:/usr/local/bin:/bin:/usr/bin",
			':');
		if (!path)
			return (NULL);
	}

	i = 0;
	while (path[i] && data->command[0][0] != '.'
		&& data->command[0][1] != '/')
	{
		command = ft_strjoin(path[i], "/");
		if (!command)
			return (ft_free_garbage(&garbage, path), NULL);
		ft_add_garbage(&garbage, command);
		command = ft_strjoin(command, data->command[0]);
		if (!command)
			return (ft_free_garbage(&garbage, path), NULL);
		ft_add_garbage(&garbage, command);
		if (access(command, X_OK) == 0)
			break ;
		i++;
	}
	if (data->command[0][0] == '.'
		&& data->command[0][1] == '/') // if command not found we check current directory
	{
		command = ft_strdup(data->command[0]);
		if (!command)
			return (ft_free_garbage(&garbage, path), NULL);
		ft_add_garbage(&garbage, command);
		if (access(command, X_OK))
			return (ft_free_garbage(&garbage, path), NULL);
	}
	if (!command)
		return (ft_free_garbage(&garbage, path), NULL);
	execve_args = malloc(sizeof(char *) * (ft_array_len(data->command) + 1));
	if (!execve_args)
		return (ft_free_garbage(&garbage, path), NULL);
	execve_args[0] = ft_strdup(command);
	i = 1;
	while (data->command[i])
	{
		execve_args[i] = data->command[i];
		i++;
	}
	execve_args[i] = NULL;
	ft_free_garbage(&garbage, path);
	return (execve_args);
}

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
		envp_array[i] = ft_strjoin(envp->key, "=");
		if (!envp_array[i])
			return (free_array(envp_array), NULL);
		if (envp->value)
		{
			temp = envp_array[i];
			envp_array[i] = ft_strjoin(envp_array[i], envp->value);
			free(temp);
			if (!envp_array[i])
				return (free_array(envp_array), NULL);
		}
		i++;
		envp = envp->next;
	}
	envp_array[i] = NULL;
	return (envp_array);
}

void	free_if_execve_fails(char **execve_args, char **envp_array)
{
	free_array(envp_array);
	if (execve_args)
	{
		free(execve_args[0]);
		free(execve_args);
	}
}

void	ft_update_shlvl(char	***envp_array)
{
	char	**tmp;
	char	*to_free;
	char	*shlvl;
	int		i;

	tmp = *envp_array;
	i = 0;
	while (tmp[i])
	{
		if (!ft_strncmp(tmp[i], "SHLVL=", 6))
		{
			to_free = tmp[i];
			shlvl = ft_itoa(ft_atoi(tmp[i] + 6) + 1);
			tmp[i] = ft_strjoin("SHLVL=", shlvl);
			free(shlvl);
			free(to_free);
			break ;
		}
		i++;
	}
}

void ft_execve(t_data *data)
{
	int		pid;
	char	**execve_args;

	execve_args = ft_get_execve_args(data);
	if (!execve_args)
	{
		if (data->command[0][0] == '.' && data->command[0][1] == '/'
			&& !access(&data->command[0][2], F_OK))
			printf("minishell: %s:Permission denied\n", data->command[0]);
		else if (data->command[0][0] == '.' && data->command[0][1] == '/')
			printf("minishell: %s: No such file or directory\n", data->command[0]);
		else
			printf("minishell: %s: command not found\n", data->command[0]);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror(strerror(errno));
		return (free_if_execve_fails(execve_args, NULL));
	}
	data->envp_array = ft_env_to_array(data->envp);
	if (!ft_strcmp(data->command[0], "./minishell") && data->envp_array)
		ft_update_shlvl(&data->envp_array);
	if (pid == 0)
	{
		if (execve(execve_args[0], execve_args, data->envp_array) == -1)
		{
			perror(strerror(errno));
			free_if_execve_fails(execve_args, data->envp_array);
			exit(1);
		}
	}
	else
	{
		if (waitpid(pid, NULL, 0) == -1)
			perror(strerror(errno));
	}
	free_if_execve_fails(execve_args, data->envp_array);
}
