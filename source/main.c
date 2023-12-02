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



void	f(){system("leaks a.out");}

int	main(void)
{
	char	*input;

	// atexit(f);
	while (1)
	{
		input = prompt();
		
		save_history(input);
	}
	return (0);
}
