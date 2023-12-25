/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamsate <shamsate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 01:19:41 by shamsate          #+#    #+#             */
/*   Updated: 2023/12/25 02:15:52 by shamsate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

//function is responsible for reading input lines, handling
// the interruption signal, writing input lines to a file descriptor,
//  and performing necessary memory management.
int	hdoc_read_handle_write(char *line, t_context *context, int fd, \
	char *delimiter)
{
	heredoc_signal(-200, context);
	signal(SIGINT, (void (*)(int))heredoc_signal);
	line = readline("> ");
	if (!line)
		return (context->data->sigflg = 1, free(context->data->delim), \
		free(line), 1);
	if (line[0])
	{
		if (!ft_strcmp(line, context->data->delim))
			return (free(context->data->delim), free(line), 1);
		if (is_quotes_exist(delimiter))
			line = expand_var_char(line, context);
		ft_putstr(line, fd);
		ft_putstr("\n", fd);
	}
	else if (ft_strlen(context->data->delim) == 0)
		return (free(context->data->delim), free(line), 1);
	free (line);
	return (0);
}

// From the context provided, it seems like this function is involved
//  in handling a "here document" in the C program. The purpose appears
//   to be to create and write to a file based on the provided delimiter
//    and then return the name of the created file. However, the specific
//     details of the ft_namegenerator,
char	*hdoc_create_wr_tofile(char *delim, t_context *dlim)
{
	char		*name;
	char		*line;
	int			fd;

	name = generate_name_tmpfile();
	dlim->data->delim = expand_delim(delim);
	line = NULL;
	fd = open(name, O_TRUNC | O_CREAT | O_RDWR, 0777);
	while (1 && fd != -1)
		if (hdoc_read_handle_write(line, dlim, fd, delim))
			break ;
	close (fd);
	return (name);
}

// it seems like this function is involved in processing "here documents"
int	process_heredoc(t_tkn	**data, t_context *context)
{
	t_tkn	*ptr;
	char	*filename;

	ptr = *data;
	while (ptr && (!(context->data->sig)))
	{
		if (ptr->type == HERDOC)
		{
			filename = hdoc_create_wr_tofile(ptr->next->val, context);
			if (!filename)
				return (1);
			free(ptr->next->val);
			ptr->next->val = filename;
		}
		ptr = ptr->next;
	}
	if (context->data->sig)
		return (1);
	return (0);
}
