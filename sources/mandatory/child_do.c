/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:21:02 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/10 16:53:17 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_do(t_process *child1, int *p_fds, t_process *data)
{
	int	fd;

	fd = valid_file(child1->path, 0);
	if (fd == -1)
	{
		ft_putstr_fd("Infile cannot be opened.\n", 2);
		ft_free(data->potential_path, get_length(data->potential_path));
		ft_free(child1->command, get_length(child1->command));
		exit(EXIT_FAILURE);
	}
	dup2(fd, 0);
	close(fd);
	close(p_fds[0]);
	dup2(p_fds[1], 1);
	close(p_fds[1]);
	if (execve(child1->command[0], child1->command, data-> envp) == -1)
	{
		ft_putstr_fd("Error in execve().\n", 2);
		ft_free(data->potential_path, get_length(data->potential_path));
		ft_free(child1->command, get_length(child1->command));
		exit(EXIT_FAILURE);
	}
}

void	child2_do(t_process *child2, int *p_fds, t_process *data)
{
	int	fd;

	fd = valid_file(child2->path, 1);
	if (fd == -1)
	{
		ft_putstr_fd("Outfile cannot be opened.\n", 2);
		ft_free(data->potential_path, get_length(data->potential_path));
		ft_free(child2->command, get_length(child2->command));
		exit(EXIT_FAILURE);
	}
	close(p_fds[1]);
	dup2(p_fds[0], 0);
	close(p_fds[0]);
	dup2(fd, 1);
	close(fd);
	if (execve(child2->command[0], child2->command, data->envp) == -1)
	{
		ft_putstr_fd("Error in execve().\n", 2);
		ft_free(data->potential_path, get_length(data->potential_path));
		ft_free(child2->command, get_length(child2->command));
		exit(EXIT_FAILURE);
	}
}
