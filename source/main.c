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
	free(input);
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

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	ft_echo(char **command)
{
	int	i;

	i = 1;
	while (command[i])
	{
		printf("%s ", command[i]);
		i++;
	}
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


void	handle_command(char **command, char **env)
{
	if (ft_strcmp(command[0], "exit") == 0)
	{
		free_array(command);
		exit(0);
	}
	else if (ft_strcmp(command[0], "echo") == 0)
		ft_echo(command);
	else if (ft_strcmp(command[0], "cd") == 0)
		ft_cd(command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		ft_pwd();
	// else if (ft_strcmp(command[0], "export") == 0)
		// ft_export(command, env);
	// else if (ft_strcmp(command[0], "unset") == 0)
	// 	ft_unset(command);
	else if (ft_strcmp(command[0], "env") == 0)
		ft_env(env);
	// else
		// ft_exec(command);
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
	data->env = setupenv_lst(env);
	if (!data->env)
	{
		free(data);
		return (NULL);
	}
	return (data);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**command;
	t_data	*data;

	(void)ac;
	(void)av;
	data = init_data(env);
	// setupenv_lst(env);
	// atexit(f);
	// while (1)
	// {
	// 	input = prompt();
	// 	command = ft_split(input, ' ');
	// 	save_history(input);
	// 	handle_command(command, env);
	// 	free_array(command);
	// }
	return (0);
}
