/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_do.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:21:02 by ymassiou          #+#    #+#             */
/*   Updated: 2024/02/26 15:22:29 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_do(char *path, int *p_fds, char **command1, char **env)
{
	int	fd;

	fd = valid_file(path, 0);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, 0);
	close(fd);
	close(p_fds[0]);
	dup2(p_fds[1], 1);
	close(p_fds[1]);
	if (execve(command1[0], command1, env) == -1)
		exit(EXIT_FAILURE);
}

void	child2_do(char *path, int *p_fds, char **command2, char **env)
{
	int	fd;

	fd = valid_file(path, 1);
	if (fd == -1)
		exit(EXIT_FAILURE);
	close(p_fds[1]);
	dup2(p_fds[0], 0);
	close(p_fds[0]);
	dup2(fd, 1);
	close(fd);
	if (execve(command2[0], command2, env) == -1)
		exit(EXIT_FAILURE);
}
