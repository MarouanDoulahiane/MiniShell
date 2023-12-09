/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 20:14:18 by mdoulahi          #+#    #+#             */
/*   Updated: 2023/12/09 18:32:43 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define BLUE "\033[1;34m"
# define YELLOW "\033[1;33m"
# define CYAN "\033[1;36m"
# define MAGENTA "\033[1;35m"
# define WHITE "\033[1;37m"
# define BLACK "\033[1;30m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define BLINK "\033[5m"
# define REVERSE "\033[7m"
# define HIDDEN "\033[8m"
# define BGBLACK "\033[40m"
# define BGRED "\033[41m"
# define RESET "\033[0m"

typedef struct s_envp
{
	bool			is_envp;
	char			*key;
	char			*value;
	struct s_envp	*next;
}				t_envp;

typedef struct s_data
{
	char	*input;
	char	**command;
	char	**envp_array;
	char	*pwd_key;
	char	*pwd_value;
	t_envp	*envp;
}				t_data;

// tools
void	ft_print_err(char *str);

// initialization
t_data	*initialize_data(char **envp);

// builtins
void	handle_builtins(t_data *data);
void	ft_pwd(t_data *data);
void	ft_cd(t_data *data);
void	ft_env(t_data *data);
void	ft_echo(t_data *data);
void	ft_unset(t_data	*data);
void	ft_exit(t_data	*data);
void	ft_export(t_data *data);

// execution
void	ft_execve(t_data *data);

// free
void	free_array(char **array);
void	free_t_envp(t_envp	*envp);
void	free_t_data(t_data	*data);

// t_envp tools
bool	ft_check_valid_key(char *str);
void	ft_declare_export(t_data *data);
void	ft_add_env(t_data *data, char *str);
void	ft_append_env(t_data *data, char *str);
bool	ft_is_key_exist(t_data *data, char *key);
void	add_back_t_envp(t_envp **envp_list, t_envp *new);
void	replace_old_t_env_value(t_data *data, char *key, char *value);

// t_envp getters
char	*ft_get_key(char *str);
char	*ft_get_value(char *str);
char	*ft_get_env(t_data *data, char *key);
t_envp	*create_t_envp(char *key, char *value);

// execve tools
char	**ft_get_path(t_data *data);
int		ft_t_envp_size(t_envp *envp);
char	**ft_env_to_array(t_envp *envp);
char	**ft_get_execve_args(t_data *data);
bool	check_command_if_it_exists_in_current_dir(t_data *data, char **command);
bool	check_command_if_it_exists_in_path(t_data *data, char **path, char **c);

#endif