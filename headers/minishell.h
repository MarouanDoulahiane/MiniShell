#ifndef HEADER_H
#define HEADER_H

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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_data
{
	char	*input;
	char	**command;
	char	**env_array;
	t_env	*env;
}				t_data;

#endif