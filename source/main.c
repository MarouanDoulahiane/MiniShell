#include "../headers/minishell.h"

char	*prompt(void)
{
	char	*input;
	char	path[1024];

	getcwd(path, sizeof(path));
	printf("%s%s %s %s: %s %s\n", REVERSE, RED, getenv("USER"), WHITE, path, RESET);
	input = readline(CYAN " >_ minishell 👽 " RESET);
	return (input);
}

bool	is_whitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && !(input[i] >= 9 && input[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

void	save_history(char *input)
{
	if (input && *input && !is_whitespace(input))
		add_history(input);
}



void	f()
{
	system("leaks minishell");
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		free(array[i++]);
	free(array);
}

void	ft_env(t_env *env_lst)
{
	while (env_lst)
	{
		printf("%s=%s\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
}

void	ft_echo(char **command)
{
	int	i;

	if (command[1] && !ft_strcmp(command[1], "-n"))
		i = 2;
	else
		i = 1;
	while (command[i])
	{
		printf("%s ", command[i]);
		i++;
	}
	if (command[1] && !ft_strcmp(command[1], "-n"))
		return ;
	printf("\n");
}

void	ft_cd(char **command)
{
	if (command[1])
	{
		if (chdir(command[1]) == -1)
			printf("cd: %s: No such file or directory\n", command[1]);
	}
	else
		chdir(getenv("HOME"));
}

void	ft_pwd(void)
{
	char	path[1024];

	getcwd(path, sizeof(path));
	printf("%s\n", path);
}

void	declare_export(t_env *env_lst)
{
	while (env_lst)
	{
		printf("declare -x %s=\"%s\"\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
}

void	ft_export(char **command, t_env **env_lst)
{
	t_env	*new;
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (command[i])
	{
		key = ft_substr(command[i], 0, ft_strchr(command[i], '=') - command[i]);
		value = ft_substr(command[i], ft_strchr(command[i], '=') - command[i] + 1, ft_strlen(command[i]));
		new = malloc(sizeof(t_env));
		if (!new)
			return ;
		new->key = key;
		new->value = value;
		new->next = *env_lst;
		*env_lst = new;
		i++;
	}
	if (!command[1])
		declare_export(*env_lst);
}

void	ft_unset(char **command, t_env **env_lst)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 1;
	while (command[i])
	{
		tmp = *env_lst;
		prev = NULL;
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, command[i]))
			{
				if (prev)
					prev->next = tmp->next;
				else
					*env_lst = tmp->next;
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}

void	handle_command(t_data **data)
{
	if (!ft_strcmp((*data)->command[0], "exit"))
		exit(0);
	else if (!ft_strcmp((*data)->command[0], "env"))
		ft_env((*data)->env);
	else if (!ft_strcmp((*data)->command[0], "echo"))
		ft_echo((*data)->command);
	else if (!ft_strcmp((*data)->command[0], "cd"))
		ft_cd((*data)->command);
	else if (!ft_strcmp((*data)->command[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp((*data)->command[0], "export"))
		ft_export((*data)->command, &(*data)->env);
	else if (!ft_strcmp((*data)->command[0], "unset"))
		ft_unset((*data)->command, &(*data)->env);
	// else if (!ft_strcmp((*data)->command[0], "history"))
		// ft_history();
	else
		printf("minishell: command not found: %s\n", (*data)->command[0]);
}

void	ft_clear_data(t_env *env_lst)
{
	t_env	*tmp;

	while (env_lst)
	{
		tmp = env_lst;
		env_lst = env_lst->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
t_env	*setup_env(char **env)
{
	t_env	*env_lst;
	t_env	*new;
	int		i;

	i = 0;
	env_lst = NULL;
	while (env[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (ft_clear_data(env_lst) ,NULL);
		new->key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		new->value = ft_substr(env[i], ft_strchr(env[i], '=') - env[i] + 1, ft_strlen(env[i]));
		new->next = env_lst;
		env_lst = new;
		i++;
	}
	return (env_lst);
}

t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = setup_env(env);
	if (!data->env)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

void	free_data(t_data *data)
{
	free_array(data->command);
	free(data->input);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = init_data(env);
	atexit(f);
	while (1)
	{
		data->input = prompt();
		if (!data->input || !*data->input || is_whitespace(data->input))
			continue ;
		data->command = ft_split(data->input, ' ');
		save_history(data->input);
		handle_command(&data);
		free_data(data);
	}
	return (0);
}
