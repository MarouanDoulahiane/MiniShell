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

void	handle_command(char **command, char **env)
{
	if (ft_strcmp(command[0], "exit") == 0)
	{
		free_array(command);
		exit(0);
	}
	// else if (ft_strcmp(command[0], "echo") == 0)
	// 	ft_echo(command);
	// else if (ft_strcmp(command[0], "cd") == 0)
	// 	ft_cd(command);
	// else if (ft_strcmp(command[0], "pwd") == 0)
	// 	ft_pwd();
	// else if (ft_strcmp(command[0], "export") == 0)
	// 	ft_export(command);
	// else if (ft_strcmp(command[0], "unset") == 0)
	// 	ft_unset(command);
	else if (ft_strcmp(command[0], "env") == 0)
		ft_env(env);
	// else
		// ft_exec(command);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**command;

	(void)ac;
	(void)av;
	atexit(f);
	while (1)
	{
		input = prompt();
		command = ft_split(input, ' ');
		save_history(input);
		handle_command(command, env);
	}
	return (0);
}
