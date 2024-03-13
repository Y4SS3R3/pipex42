/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:50:31 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/13 11:32:56 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	find_limiter(char *limiter, char *line, char *tmp)
{
	if (ft_strcmp(limiter, tmp) == 0)
	{
		free(line);
		free(tmp);
		return (0);
	}
	return (1);
}

void	fill_heredoc(char *limiter, t_process *data, char *name)
{
	int		read;
	char	*line;
	char	*tmp;

	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		read = get_next_line(&line);
		if (read == 0)
		{
			write(1, "\n", 1);
			return ;
		}
		if (read == -1)
		{
			close(data->out_fd);
			close(data->here_doc_fd);
			free(name);
			error_ii("Problem reading from the here_doc file.\n", data, line);
		}
		tmp = ft_substr(line, 0, ft_strlen(line) - 1);
		if (tmp == NULL)
		{
			close(data->out_fd);
			close(data->here_doc_fd);
			free(name);
			error_ii("Malloc() error.\n", data, line);
		}
		if (find_limiter(limiter, line, tmp) == 0)
			return ;
		if (write(data->here_doc_fd, line, ft_strlen(line)) == -1)
		{
			close(data->out_fd);
			close(data->here_doc_fd);
			free(name);
			error_iii("Write() error.\n", tmp, data, line);
		}
		free(tmp);
		free(line);
	}
}
/*fd leaks*/
/*name ptr leak in fill_heredoc*/
/**/

char	*randomize_file_name(void)
{
	int		i;
	char	*name;
	char	*tmp;

	i = 0;
	name = NULL;
	while (i < FOPEN_MAX)
	{
		name = ft_itoa(i);
		tmp = name;
		name = ft_strjoin("/tmp/", name);
		free(tmp);
		if (access(name, F_OK) == -1)
			return (name);
		free(name);
		i++;
	}
	return (NULL);
}

void	hrdc_arg_error(t_process *data)
{
	char	*m;

	m = "->Usage: ./pipex_bonus here_doc LIMITER cmd1 cmd2 cmd3 ... OUTFILE.\n";
	write(2, "->here_doc needs 6 arguments at least.\n", 40);
	write(2, m, 69);
	close(data->out_fd);
	exit(EXIT_FAILURE);
}

void	heredocing_time(int ac, char *limiter, t_process *data)
{
	char	*name;

	if (ac < 6)
		hrdc_arg_error(data);
	name = randomize_file_name();
	data->here_doc_fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data->here_doc_fd == -1)
		return(close(data->out_fd), error_ii("Failure while opening here_doc file.\n", data, name));
	fill_heredoc(limiter, data, name);
	close(data->here_doc_fd);
	data->here_doc_fd = open(name, O_RDONLY);
	if (data->here_doc_fd == -1)
		return(close(data->out_fd), error_ii("Open() failed.\n", data, name));
	if (dup2_more(data->here_doc_fd, 0) == -1)
		return(close(data->out_fd), error_ii("Unexpected error[1].\n", data, name));
	if (unlink(name) == -1)
		return(close(data->out_fd), error_ii("Problem unlinking the file.\n", data, name));
	free(name);
}
