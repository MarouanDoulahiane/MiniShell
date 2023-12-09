/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:20:14 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/09 18:52:47 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

bool	is_whitespace(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13))
			return (false);
		i++;
	}
	return (true);
}

char	*prompt(void)
{
	char	*input;

	input = readline(" >_ minishell $ ");
	while (1)
	{
		if (input && !is_whitespace(input))
			break ;
		free(input);
		input = readline(" >_ minishell $ ");
	}
	return (input);
}

// void	save_history(char *input)
// {
// 	int		i;
// 	bool	is_whitespace;

// 	i = 0;
// 	is_whitespace = true;
// 	while (input[i])
// 	{
// 		if (input[i] != ' ' && !(input[i] >= 9 && input[i] <= 13))
// 			is_whitespace = false;
// 		i++;
// 	}
// 	if (input && *input && !is_whitespace)
// 		add_history(input);
// }

void	f(void)
{
	system("leaks minishell");
}

void	free_data(t_data *data, bool free_envp, bool free_command)
{
	if (free_envp)
	{
		free_t_envp(data->envp);
		free_array(data->envp_array);
	}
	if (free_command)
		free_array(data->command);
	free(data->input);
}


int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = initialize_data(envp);
	if (!data)
		return (1);
	// atexit(f);
	while (1)
	{
		data->input = prompt();
		data->command = ft_split(data->input, ' ');
		if (!data->command)
		{
			free_data(data, false, true);
			continue ;
		}
		add_history(data->input);
		handle_builtins(data);
		free_data(data, false, true);
	}
	return (0);
}
