# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoulahi <mdoulahi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/02 21:34:54 by shamsate          #+#    #+#              #
#    Updated: 2023/12/26 02:50:17 by mdoulahi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

YELLOW	=	$(shell tput -Txterm setaf 4)
GREEN	=	$(shell tput -Txterm setaf 5)

C_BLUE  = \033[1;34m
C_CYAN  = \033[1;36m
C_RESET = \033[34m

CC      = cc

LIB =  -L ~/brew/opt/readline/lib
INC =  -I ~/brew/opt/readline/include

RM      = rm -rf

CFLAGS  =   -Wall -Wextra -Werror

READLINE = -lreadline

HEADER  = include/minishell.h

O_DIR   := OBJ_DER

PARS = $(addprefix src/parsing/, dependencies/check_utils_synx.c dependencies/cmd_add_clear.c dependencies/get_command.c \
	dependencies/in_out_file.c dependencies/lst_add_clear.c dependencies/tkn_data_check.c dependencies/tkn_data_check_part2.c \
	dependencies/tokenizer_and_start.c lexer/add_cmd_token.c lexer/check_cmd_data.c expand/expand_utils.c expand/name_expand.c\
	expand/expand.c heredoc/heredoc_utils.c heredoc/heredoc.c)



EXEC = $(addprefix src/execution/, pipe/excute.c pipe/final_execute.c pipe/first_pipe.c pipe/middle_pipe.c \
		pipe/last_pipe.c pipe/tools.c init_helper.c \
		execve/execve_main.c execve/execve_tools.c execve/execve_tools_2.c initialize_data.c free.c \
		builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_exit.c \
		builtins/ft_export.c builtins/ft_pwd.c builtins/ft_unset.c tools/t_envp_tools.c \
		tools/ft_print_err.c tools/replace_old_t_env_value.c tools/t_envp_getters.c )


UTIL = $(addprefix utils_libft/, ft_atoi.c free_tab.c ft_bzero.c ft_strlen.c ft_strcmp.c ft_joinstr.c ft_strdup.c \
	ft_split.c ft_putstr_fd.c ft_putchar_fd.c ft_itoa.c ft_strchr.c ft_realloc.c ft_memmove.c \
	ft_memcpy.c ft_calloc.c ft_strncmp.c ft_joinchar.c ft_isdigit.c ft_isalpha.c ft_isalnum.c ft_memset.c \
	ft_substr.c ft_cmd_isdigit.c )


M_SRCS = main.c $(UTIL) $(EXEC) $(PARS)

M_OBJS = $(patsubst %.c,$(O_DIR)/%.o,$(M_SRCS))

all: $(NAME)

Prj_Name = "\n" \
	"$(YELLOW)███$(GREEN)╗   $(YELLOW)███$(GREEN)╗ $(YELLOW)██$(GREEN)╗ $(YELLOW)███$(GREEN)╗  $(YELLOW)\
	██$(GREEN)╗ $(YELLOW)██$(GREEN)╗ $(YELLOW)███████$(GREEN)╗ $(YELLOW)██$(GREEN)╗  $(YELLOW)██$(GREEN)╗ \
	$(YELLOW)███████$(GREEN)╗ $(YELLOW)██$(GREEN)║      $(YELLOW)██$(GREEN)║     \n" \
	"$(YELLOW)████$(GREEN)╗ $(YELLOW)████$(GREEN)║ $(YELLOW)██$(GREEN)║ $(YELLOW)████$(GREEN)╗  $(YELLOW)██$(GREEN)║\
	 $(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)╔════╝ $(YELLOW)██$(GREEN)║  $(YELLOW)██$(GREEN)║\
	  $(YELLOW)██$(GREEN)╔════╝ $(YELLOW)██$(GREEN)║      $(YELLOW)██$(GREEN)║     \n" \
	"$(YELLOW)██$(GREEN)╔$(YELLOW)████$(GREEN)╔$(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)║ \
	$(YELLOW)██$(GREEN)╔$(YELLOW)██$(GREEN)╗ $(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)║\
	 $(YELLOW)███████$(GREEN)╗ $(YELLOW)███████$(GREEN)║ \
	 $(YELLOW)█████$(GREEN)╗   $(YELLOW)██$(GREEN)║      $(YELLOW)██$(GREEN)║     \n" \
	"$(YELLOW)██$(GREEN)║╚$(YELLOW)██$(GREEN)╔╝$(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)║\
	 $(YELLOW)██$(GREEN)║╚$(YELLOW)██$(GREEN)╗$(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)║ \
	 ╚════$(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)╔══$(YELLOW)██$(GREEN)║ \
	 $(YELLOW)██$(GREEN)╔══╝   $(YELLOW)██$(GREEN)║      $(YELLOW)██$(GREEN)║     \n" \
	"$(YELLOW)██$(GREEN)║ $(GREEN)╚═╝ $(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)║ $(YELLOW)██$(GREEN)║ \
	$(GREEN)╚$(YELLOW)████$(GREEN)║ $(YELLOW)██$(GREEN)║ $(YELLOW)███████$(GREEN)║ \
	$(YELLOW)██$(GREEN)║  $(YELLOW)██$(GREEN)║ $(YELLOW)███████$(GREEN)╗ $(YELLOW)███████$(GREEN)╗ $(YELLOW)███████$(GREEN)╗\n" \
	"$(GREEN)╚═╝     $(GREEN)╚═╝ $(GREEN)╚═╝ $(GREEN)╚═╝  $(GREEN)╚═══╝ $(GREEN)╚═╝\
	 $(GREEN)╚══════╝ $(GREEN)╚═╝  $(GREEN)╚═╝ $(GREEN)╚══════╝ $(GREEN)╚══════╝\
	  $(GREEN)╚══════╝\n$(C_RESET)\033[0m" \


$(NAME): $(M_OBJS) $(HEADER)
	@echo $(Prj_Name)
	@$(CC) $(CFLAGS) $(M_OBJS) $(READLINE) $(LIB) -o $(NAME)
	@echo "\n 			-  Execution ready..✔️\n"

$(O_DIR)/%.o: %.c $(HEADER)
	@echo "- Making Object file $(notdir $@) from source file $(notdir $<)...\n"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@$(RM) $(O_DIR)
	@echo "\n- Object file Removed. ✔️\n"

fclean: clean
	@$(RM) $(NAME)
	@echo "- Removing $(NAME) ..\n"
	@echo "- Removed. ✔️\n"

re: fclean all

.PHONY: all clean fclean re