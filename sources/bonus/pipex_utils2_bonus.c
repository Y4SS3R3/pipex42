/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:36:50 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/10 22:47:26 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_child(t_process *data, int out_fd)
{
	if (dup2_more(out_fd, 1) == -1)
	{
		write(2, "Unexpected error[4].\n", 21);
		ft_free(data->potential_path, get_length(data->potential_path));
		ft_free(data->command, get_length(data->command));
		exit(EXIT_FAILURE);
	}
	if (execve(data->command[0], data->command, data->envp) == -1)
	{
		write(2, "Execve() error.\n", 16);
		ft_free(data->potential_path, get_length(data->potential_path));
		ft_free(data->command, get_length(data->command));
		exit(EXIT_FAILURE);
	}
}

void	pass_command(t_process *data, char *command_av)
{
	int		flag;
	char	*tmp;

	flag = 0;
	if (close(data->end[0]) == -1)
		error_iv("Close() problem.\n", data); // FDS // NAME
	if (dup2_more(data->end[1], 1) == -1) // CLOSE FD 0 / 1 / INFILE / OUTFILE / NAME
		error_iv("Dup2() problem.\n", data);
	data->command = ft_split(command_av, ' ');
	tmp = data->command[0];
	data->command[0] = check_command(data->command[0],
			data->potential_path, &flag);
	if (ft_strcmp(data->command[0], tmp) > 0 && flag != 0)
	{
		free(tmp);
		tmp = NULL;
	}
	if (data->command[0] == NULL)
		error_v("Command not found.\n", data); // CLOSE FD 0 / 1 / INFILE / OUTFILE / NAME
	if (execve(data->command[0], data->command, data->envp) == -1)
		error_v("Execve() error.\n", data); // CLOSE FD 0 / 1 / INFILE / OUTFILE / NAME
}

int	dup2_more(int old, int new)
{
	int	ret1;
	int	ret2;

	ret1 = dup2(old, new);
	ret2 = close(old);
	if (ret1 == -1 || ret2 == -1)
		return (-1);
	return (0);
}

void	last_free(t_process *data)
{
	ft_free(data->potential_path, get_length(data->potential_path));
	ft_free(data->command, get_length(data->command));
}

void	close_both(t_process *data, int out_fd)
{
	if (close(0) == -1)
		error_v("Close() error.\n", data);
	if (close(out_fd) == -1)
		error_v("Close() error.\n", data);
}
