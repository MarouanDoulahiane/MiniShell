/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:28:44 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/26 02:21:23 by mdoulahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdio.h>  // for printf
# include <stdlib.h> // for malloc and free getenv
# include <unistd.h> // for write, access, open, read, close, fork
# include <limits.h> // for LLONG_MAX and LLONG_MIN
# include <signal.h> //for signal,sigaction,sigemptyset,sigaddset,kill,exit
# include <fcntl.h>      // for file-related functions
# include <dirent.h>     // for opendir, readdir, closedir
# include <string.h>     // for strerror, perror
# include <termios.h>    // for terminal-related functions
# include <unistd.h>     // for isatty, ttyname, ioctl
# include <curses.h>     // for terminal handling functions (curses library)
# include <sys/stat.h>   // for stat, lstat, fstat
# include <readline/readline.h> // for rl_on_new_ln rl_repl_line rl_redisp
# include <readline/history.h> // for rl_clear_history add_history
# include <sys/wait.h>   // for wait, waitpid
# include <sys/types.h>  // for getpid
# include <errno.h>

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

# define START  "\n \
	\033[1;31m███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗  ███████╗ ██║      ██║     \033[34m\n\
	\033[1;31m████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║  ██╔════╝ ██║      ██║     \033[34m\n\
	\033[1;31m██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║  █████╗   ██║      ██║     \033[34m\n\
	\033[1;31m██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║  ██╔══╝   ██║      ██║     \033[34m\n\
	\033[1;31m██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║  ███████╗ ███████╗ ███████╗ \033[34m\n\
	\033[1;31m╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝  ╚══════╝ ╚══════╝ ╚══════╝ \033[34m\n\
	\033[1;31m                                                             \
	  BY: R4v3n. \033[34m\033[0m\n"

typedef struct s_envp
{
	char			*content;
	bool			is_envp;
	char			*key;
	char			*value;
	struct s_envp	*next;
}				t_envp;

typedef struct s_info
{
	char	*input;
	char	**command;
	char	**envp_array;
	char	*pwd_key;
	char	*pwd_value;
	bool	allowed_path;
	t_envp	*envp;
}				t_info;

//parse
typedef enum e_types
{
	NUl,
	CMD,
	ARG,
	INF,
	OUTF,
	POUT,
	DELIM,
	OUTP,
	PEND,
	INP,
	PIPE,
	HERDOC,
}	t_types;

//execution
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	t_envp		*env;
	int			sig;
	int			sigflg;
	int			f_stdin;
	int			f_stdout;
	int			flg;
	char		*delim;
}				t_data;

typedef struct s_context
{
	t_data	*data;
}				t_context;

int	g_ext_status;

typedef struct s_comd
{
	char			*comd;
	char			**argms;
	int				inp;
	int				outp;
	int				errp;
	struct s_comd	*next;
}					t_comd;

typedef struct s_tkn // ls -la | grep "text"
{
	char			*val; //
	t_types			type;
	int				error;
	int				flg;
	struct s_tkn	*next;
	struct s_tkn	*prev;
}					t_tkn;

typedef enum e_err
{
	SUCC,
	ERRR,
	ERR1,
	CMD_EXE_FAILED = 126,
	CMD_NOT_EXIST = 127,
	SNTX_ERR = 258,
}	t_err;

//////////////////////////////////////////////////////////////////////////////

// pipes
void		excute(t_comd *cmd, t_context *context, t_info *info);
void		final_execute(t_comd *cmd, t_info *info);
void		first_pipe(int **fd, int *i, t_comd *cmd, t_info *info);
void		middle_pipe(int **fd, int *i, t_comd *cmd, t_info *info);
void		last_pipe(int **fd, int *i, t_comd *cmd, t_info *info);
void		execute_builtins(t_comd *cmd, t_info *info);

	// tools
int			**create_fds(int size);
int			ft_cmd_len(t_comd *cmd);
void		close_fds_and_free_and_wait_to_set_status(int **fd,
				t_comd *cmd);
int			are_builin(t_comd *cmd);

// tools
void		ft_print_err(char *str, int fd);
t_tkn		*init(t_context *context);

// initialization
t_info		*initialize_data(char **envp);

// builtins
void		ft_export_update_content(t_info *info);
void		handle_builtins(t_info *data);
void		ft_pwd(t_info *data, t_comd *cmd);
void		ft_cd(t_comd *cmd, t_info *data);
void		ft_env(t_comd *cmd, t_info *data);
void		ft_echo(t_comd *cmd);
void		ft_unset(t_comd *cmd, t_info *info);
void		ft_exit(t_comd *cmd);
void		ft_export(t_comd *cmd, t_info *data);

// execution
void		ft_execve(t_comd *cmd, t_info *data);

// free
void		free_array(char **array);
void		free_t_envp(t_envp	*envp);
// void	free_t_data(t_info	*data);
void		free_t_info(t_info	*data);

// t_envp tools
bool		check_is_valid_arg_for_export(char *str);
void		ft_declare_export(t_info *data, t_comd *cmd);
void		ft_add_env(t_info *data, char *str);
void		ft_append_env(t_info *data, char *str);
bool		ft_is_key_exist(t_info *data, char *key);
void		add_back_t_envp(t_envp **envp_list, t_envp *new);
void		replace_old_t_env_value(t_info *data, char *key, char *value);

// t_envp getters
char		*ft_get_key(char *str);
char		*ft_get_value(char *str);
char		*ft_get_env(t_info *data, char *key);
t_envp		*create_t_envp(char *key, char *value);

// execve tools
char		**ft_get_path(t_info *data);
int			ft_t_envp_size(t_envp *envp);
char		**ft_env_to_array(t_envp *envp);
char		**ft_get_execve_args(t_comd *cmd, t_info *data);
bool		check_command_if_it_exists_in_current_dir(t_comd *cmd,
				char **command);
bool		check_command_if_it_exists_in_path(t_comd *cmd,
				char **path, char **command);

//////////////////////////////////////////////////////////////////////////////

// tkn & data list...
t_tkn		*ft_new_tkn(char *data);
void		ft_add_tkn_back(t_tkn **data, t_tkn *new_dt);
void		free_val_tkn(t_tkn *lst);
void		free_clen_data(t_tkn **lst);
// commande list ...
t_comd		*ft_lastcmd_node(t_comd *cmd);
void		add_cmd_back(t_comd **cmd, t_comd *new_c);
void		free_arg_cmd(t_comd *cmd);
void		free_node_clean(t_comd **cmd);
int			cmd_size(t_comd *cmd);
// parsing ...
int			is_val_char(int c);
int			check_quotes(char *cmd, int idx);
int			check_red_pipe(char c, char *cmd, int idx);
void		check_sin_quotes(char *cmd, int *i, int *check);
int			check_both_quotes(char *cmd);
void		command_init(t_comd	*cmd);
void		check_update_cmd(t_comd **new_c);
void		add_cmd_list(t_comd **cmd, t_comd **new_c);
int			is_reder(int var);
int			check_reder_tkn(t_tkn **data);
int			check_pipe_red_herdoc(t_tkn **data);
int			is_a_directory(char *str);
int			check_cmd_isdretory(char *str);
void		handle_get_cmd(t_tkn **data, t_comd **cmd, t_context *context);
int			check_syx_quotes_err(char *line);
int			tokenize_inp_cmd(char *cmd, t_tkn **data, t_context *context);
int			proc_valid_cmd(char *line, t_tkn *data, t_comd **cmd,
				t_context *cont);
t_context	*initialize_context(t_envp *envp);
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
//signal....main
void		handle_signal_ctrl_c(int sig, t_context *context);
void		handle_signal_in_out(t_context *context);

//in_out_file...
void		update_outfile(t_comd **command, char *file_path, t_tkn *token);
void		check_red_open(t_comd **cmd, char *val, t_tkn *ptr);
void		check_append_outerr(t_comd **cmd, char *val, t_tkn *ptr);
int			check_err_pipe(t_tkn *data);
void		handle_in_out(t_tkn *ptr, t_comd **cmd);
//lexer
int			is_red_char(char c);
void		add_operator_tkn(t_tkn **data, char *cmd, int *idx);
void		cmd_to_str_add(t_tkn **data, char *cmd, int *idx);
void		modify_cmd_if(t_tkn	**data, t_context *context);
//expand....
int			is_quotes_exist(char *str);
int			cont_no_wspace(char *str);
char		*if_contain_env_var(char *str, t_context *context);
char		*extract_value_checkname(char *val, int	*idx, t_context *context);
void		get_val_concat(char	*val, int *i, char **str, t_context *context);
void		append_char_str(char *val, char **str, int i);
char		*expand_var_char(char *val, t_context *context);
char		*expand_var_str(char *val, t_context *context);
char		*expand_delim(char *delim);
void		expand_check_update_cmdargs(t_tkn *ptr, t_comd *new_c);
// heredoc.....
char		*generate_name_tmpfile(void);
void		heredoc_signal(int sig, t_context *context);
int			hdoc_rd_handle_wt(char *line, char *delim, int fd, char *delimiter);
char		*hdoc_create_wr_tofile(char *delim, t_context *dlim);
int			process_heredoc(t_tkn	**data, t_context *context);
// utils_libft....
void		free_tab(char **tab);
size_t		ft_strlen(const char *str);
char		*ft_joinchar(char *str, char c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
char		*ft_strdup(const char *str);
void		ft_putchar(char c, int fd);
void		ft_putstr(char *str, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char *s1, char const *s2);
char		*ft_itoa(int nbr);
char		*ft_strchr(const char *str, int c);
void		*ft_calloc(size_t nbr, size_t size);
void		ft_bzero(void *str, size_t nb);
char		**ft_split(char const *s, char c);
char		**ft_realloc(char **tab, char *str);
void		*ft_memset(void *str, int c, size_t len);
void		check_red_open(t_comd **cmd, char *val, t_tkn *ptr);
// void	loop_and_process_exec_cmd(t_tkn *data, t_comd *cmd, \
// 	t_context *context);
int			ft_atoi(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
bool		ft_cmd_isdigit(char *str);

#endif
