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
		if (env_lst->value)
			printf("%s=%s\n", env_lst->key, env_lst->value);
		env_lst = env_lst->next;
	}
}

bool	check_is_dash_n_for_echo(char *command)
{
	int	i;

	i = 0;
	if (command[i] != '-')
		return (0);
	i++;
	if (command[i] != 'n')
		return (0);
	i++;
	while (command[i])
	{
		if (command[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **command)
{
	int		i;
	bool	is_dash_n;

	i = 1;
	is_dash_n = 0;
	while (command[i] && check_is_dash_n_for_echo(command[i]))
	{
		is_dash_n = 1;
		i++;
	}
	while (command[i])
	{
		printf("%s", command[i]);
		if (command[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

bool	replace_old_value_if_exist(t_env **env_lst, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_cd(char **command, t_env **env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (command[1])
	{
		if (chdir(command[1]) == -1)
			printf("cd: %s: No such file or directory\n", command[1]);
	}
	else
		chdir(getenv("HOME"));
	replace_old_value_if_exist(env, "OLDPWD", path);
	replace_old_value_if_exist(env, "PWD", getcwd(NULL, 0));
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
		if (!ft_strcmp(env_lst->key, "_"))
		{
			env_lst = env_lst->next;
			continue ;
		}
		printf("declare -x %s", env_lst->key);
		if (env_lst->value) // check if we have value or not
			printf("=\"%s\"", env_lst->value);
		printf("\n");
		env_lst = env_lst->next;
	}
}
void	add_at_the_end_of_env_lst(t_env **env_lst, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	new->next = NULL;
	if (!*env_lst)
	{
		*env_lst = new;
		return ;
	}
	tmp = *env_lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}


bool	check_if_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i] != '=' && key[i])
	{
		if (key[i] == '+' && key[i + 1] == '=')
			return (1);
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_the_env(t_env *env_lst, char *key)
{
	while (env_lst)
	{
		if (!ft_strcmp(env_lst->key, key))
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void	ft_export(char **command, t_env **env_lst)
{
	char	*key;
	char	*value;
	char	*tmp;
	int		i;

	i = 1;
	while (command[i])
	{
		if(!check_if_valid_key(command[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", command[i]);
			i++;
			continue ;
		}
		tmp = ft_strchr(command[i], '+');
		if (tmp && tmp[1] == '=')
		{
			key = ft_substr(command[i], 0, ft_strchr(command[i], '+') - command[i]);
			value = ft_strjoin(get_the_env(*env_lst, key), ft_strchr(command[i], '=') + 1);
			if (!value)
				value = ft_strdup(ft_strchr(command[i], '=') + 1);
		}
		else if (!ft_strchr(command[i], '='))
		{
			key = ft_strdup(command[i]);
			value = NULL;
		}
		else
		{
			key = ft_substr(command[i], 0, ft_strchr(command[i], '=') - command[i]);
			value = ft_substr(command[i], ft_strchr(command[i], '=') - command[i] + 1, ft_strlen(command[i]));
		}
		if (!replace_old_value_if_exist(env_lst, key, value))
			add_at_the_end_of_env_lst(env_lst, key, value);
		i++;
	}
	if (!command[1])
		declare_export(*env_lst);
}

bool	check_if_valid_unset_identifier(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(char **command, t_env **env_lst)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 1;
	while (command[i])
	{
		if (!check_if_valid_unset_identifier(command[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", command[i]);
			i++;
			continue ;
		}
		tmp = *env_lst;
		prev = NULL;
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, command[i]) && ft_strcmp(tmp->key, "_"))
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

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**ft_creat_argv_for_execve(t_data *data)
{
	char	**execve_argv;
	char	**path;
	char	*command;
	char	secure_path[41];
	char	*tmp;
	int		i;

	command = NULL;
	path = ft_split(getenv("PATH"), ':');
	ft_strlcpy(secure_path, "usr/gnu/bin:/usr/local/bin:/bin:/usr/bin", 41);
	if (!path)
	{
		path = ft_split(secure_path, ':');
		if (!path)
			return (NULL);
	}
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		command = ft_strjoin(tmp, data->command[0]);
		free(tmp);
		if (!access(command, X_OK))
			break ;
		free(command);
		command = NULL;
		i++;
	}
	if (!command)
	{
		command = ft_strdup(data->command[0]);
		if (!access(command, X_OK))
		{
			if (!ft_strcmp(data->command[0], "./minishell") && get_the_env(data->env, "SHLVL"))
				replace_old_value_if_exist(&data->env, "SHLVL", ft_itoa(ft_atoi(get_the_env(data->env, "SHLVL")) + 1));
		}
		else
			return (free(command), NULL);
	}
	execve_argv = malloc(sizeof(char *) * (ft_array_len(data->command) + 1));
	if (!execve_argv)
		return (free_array(path), NULL);
	execve_argv[0] = command;
	i = 1;
	while (data->command[i])
	{
		execve_argv[i] = data->command[i];
		i++;
	}
	execve_argv[i] = NULL;
	free_array(path);
	return (execve_argv);
}

int	t_env_size(t_env *env_lst)
{
	int	i;

	i = 0;
	while (env_lst)
	{
		i++;
		env_lst = env_lst->next;
	}
	return (i);
}

char	**get_the_env_from_lst(t_env *env_lst)
{
	char	**env;
	int		i;

	i = 0;
	env = malloc(sizeof(char *) * (t_env_size(env_lst) + 1));
	if (!env)
		return (NULL);
	while (env_lst)
	{
		env[i] = ft_strjoin(env_lst->key, "=");
		if (env_lst->value)
			env[i] = ft_strjoin(env[i], env_lst->value);
		i++;
		env_lst = env_lst->next;
	}
	env[i] = NULL;
	return (env);
}

void ft_execve(t_data *data) {
    int pid;
    int status;
    char **execve_argv;

	execve_argv = ft_creat_argv_for_execve(data);
	if (!execve_argv) {
		printf("minishell: %s: command not found\n", data->command[0]);
		return ;
	}
    pid = fork();
    if (pid == -1)
	{
        perror("fork");
        return;
    }
    if (pid == 0)
	{
        execve(execve_argv[0], execve_argv, get_the_env_from_lst(data->env));
        perror("execve");
        exit(EXIT_FAILURE);
    }
	else
	{
        if (waitpid(pid, &status, 0) == -1)
		{
            perror("waitpid");
            return;
        }
    }
	free(execve_argv[0]);
	free(execve_argv); 
}

bool	are_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	if (i == 1)
		exit(EXIT_SUCCESS);
	else if (i == 2)
	{
		if (are_digits(command[1]))
		{
			printf("exit\n");
			exit(ft_atoi(command[1]));
		}
		else
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n", command[1]);
			exit(255);
		}
	}
	else
	{
		if (are_digits(command[1]))
			printf("exit\nminishell: exit: too many arguments\n");
		else
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n", command[1]);
			exit(255);
		}
	}
}

void	handle_command(t_data **data)
{
	if (!ft_strcmp((*data)->command[0], "exit"))
		ft_exit((*data)->command);
	else if (!ft_strcmp((*data)->command[0], "env"))
		ft_env((*data)->env);
	else if (!ft_strcmp((*data)->command[0], "echo"))
		ft_echo((*data)->command);
	else if (!ft_strcmp((*data)->command[0], "cd"))
		ft_cd((*data)->command, &(*data)->env);
	else if (!ft_strcmp((*data)->command[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp((*data)->command[0], "export"))
		ft_export((*data)->command, &(*data)->env);
	else if (!ft_strcmp((*data)->command[0], "unset"))
		ft_unset((*data)->command, &(*data)->env);
	else
		ft_execve(*data);
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


t_env	*setup_env_when_we_dont_have_it(void)
{
	t_env	*env_lst;

	env_lst = NULL;
	add_at_the_end_of_env_lst(&env_lst, ft_strdup("OLDPWD"), NULL);
	add_at_the_end_of_env_lst(&env_lst, ft_strdup("PWD"), getcwd(NULL, 0));
	add_at_the_end_of_env_lst(&env_lst, ft_strdup("SHLVL"), ft_strdup("1"));
	add_at_the_end_of_env_lst(&env_lst, ft_strdup("_"), ft_strdup("/usr/bin/env"));

	return (env_lst);
}

t_env	*setup_env(char **env)
{
	t_env	*env_lst;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	env_lst = NULL;
	if (!*env)
		return (setup_env_when_we_dont_have_it());
	while (env[i])
	{
		key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		value = ft_substr(env[i], ft_strchr(env[i], '=') - env[i] + 1, ft_strlen(env[i]));
		add_at_the_end_of_env_lst(&env_lst, ft_strdup(key), ft_strdup(value));
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
	data->env_array = env;
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
	// atexit(f);
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
