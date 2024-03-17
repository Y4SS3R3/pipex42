/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:36:50 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/17 03:36:11 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_child(t_process *data)
{
	if (dup2_more(data->out_fd, 1) == -1)
		error_v("Unexpected error[4].\n", data);
	if (execve(data->command[0], data->command, data->envp) == -1)
		error_v("Execve() error.\n", data);
}

void	pass_command(t_process *data, char *command_av)
{
	int		flag;
	char	*tmp;

	flag = 0;
	close(data->end[0]);
	if (dup2_more(data->end[1], 1) == -1)
	{
		close(data->out_fd);
		error_iv("Dup2() problem.\n", data);
	}
	data->command = ft_splitws(command_av);
	if (data->command == NULL)
		custom_error6(data, "Unexpected error[5].\n");
	tmp = data->command[0];
	data->command[0] = check_command(data->command[0],
			data->potential_path, &flag);
	if (ft_strcmp(data->command[0], tmp) > 0 && flag != 0)
		free(tmp);
	if (data->command[0] == NULL)
		custom_error2("Command not found.\n", data);
	if (execve(data->command[0], data->command, data->envp) == -1)
		custom_error2("Execve() error.\n", data);
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
	ft_free(data->potential_path, get_length(data->potential_path), 0);
	ft_free(data->command, get_length(data->command), 0);
}

// void	close_both(t_process *data)
// {
// 	close(0);
// 	close(data->out_fd);
// }
