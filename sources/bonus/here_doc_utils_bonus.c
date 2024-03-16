/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:04:35 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/14 17:07:24 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_both(char *tmp, char *line)
{
	free(tmp);
	free(line);
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

void	custom_error3(char *message, t_process *data, char *name, char *line)
{
	close(data->out_fd);
	close(data->here_doc_fd);
	free(name);
	error_ii(message, data, line);
}

void	custom_error4(t_process *data, char *tmp, char *line, char *name)
{
	close(data->out_fd);
	close(data->here_doc_fd);
	free(name);
	error_iii("Write() error.\n", tmp, data, line);
}
