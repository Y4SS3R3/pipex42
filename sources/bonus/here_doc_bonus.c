/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:50:31 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/17 02:33:14 by ymassiou         ###   ########.fr       */
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
			custom_error3("Problem reading from the here_doc file.\n",
				data, name, line);
		tmp = ft_substr(line, 0, ft_strlen(line) - 1);
		if (tmp == NULL)
			custom_error3("Malloc() error.\n", data, name, line);
		if (find_limiter(limiter, line, tmp) == 0)
			return ;
		if (write(data->here_doc_fd, line, ft_strlen(line)) == -1)
			custom_error4(data, tmp, line, name);
		free_both(tmp, line);
	}
}

void	use_here_doc(int ac, char *limiter, t_process *data)
{
	char	*name;

	if (ac < 6)
		hrdc_arg_error(data);
	name = randomize_file_name();
	data->here_doc_fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data->here_doc_fd == -1)
		return (close(data->out_fd),
			error_ii("Failure while opening here_doc file.\n", data, name));
	fill_heredoc(limiter, data, name);
	close(data->here_doc_fd);
	data->here_doc_fd = open(name, O_RDONLY);
	if (data->here_doc_fd == -1)
		return (close(data->out_fd), error_ii("Open() failed.\n", data, name));
	if (dup2_more(data->here_doc_fd, 0) == -1)
		return (close(data->out_fd),
			error_ii("Unexpected error[1].\n", data, name));
	if (unlink(name) == -1)
		return (close(data->out_fd),
			error_ii("Problem unlinking the file.\n", data, name));
	free(name);
}
