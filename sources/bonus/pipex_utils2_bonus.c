/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:36:50 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/11 15:50:20 by ymassiou         ###   ########.fr       */
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

void	pass_command1(t_process *data, char *command_av)
{
	int		flag;
	char	*tmp;

	flag = 0;
	close(data->end[0]);
	if (dup2_more(data->end[1], 1) == -1)
	{
		close(data->end[0]);
		close(data->in_fd);
		close(data->out_fd);
		error_iv("Dup2() problem.\n", data);
	}
	data->command = ft_split(command_av, ' ');
	tmp = data->command[0];
	data->command[0] = check_command(data->command[0],
			data->potential_path, &flag);
	if (ft_strcmp(data->command[0], tmp) > 0 && flag != 0)
		free(tmp);
	if (data->command[0] == NULL)
	{
		close(data->end[0]);
		close(data->in_fd);
		close(data->out_fd);
		error_v("Command not found.\n", data);
	}
	if (execve(data->command[0], data->command, data->envp) == -1)
	{
		close(data->end[0]);
		close(data->in_fd);
		close(data->out_fd);
		error_v("Execve() error.\n", data); // CLOSE FD 0 / 1 / INFILE / OUTFILE / NAME
	}
}
void	pass_command2(t_process *data, char *command_av)
{
	int		flag;
	char	*tmp;

	flag = 0;
	close(data->end[0]);
	if (dup2_more(data->end[1], 1) == -1)
	{
		close(data->end[0]);
		close(data->out_fd);
		error_iv("Dup2() problem.\n", data);
	}
	data->command = ft_split(command_av, ' ');
	tmp = data->command[0];
	data->command[0] = check_command(data->command[0],
			data->potential_path, &flag);
	if (ft_strcmp(data->command[0], tmp) > 0 && flag != 0)
		free(tmp);
	if (data->command[0] == NULL)
	{
		close(data->end[0]);
		close(data->out_fd);
		error_v("Command not found.\n", data);
	}
	if (execve(data->command[0], data->command, data->envp) == -1)
	{
		close(data->end[0]);
		close(data->out_fd);
		error_v("Execve() error.\n", data); // CLOSE FD 0 / 1 / INFILE / OUTFILE / NAME
	}
}

int	dup2_more(int old, int new)
{
	int	res;

	res = dup2(old, new);
	close(old);
	if (res == -1)
		return (res);
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
