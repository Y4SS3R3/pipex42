/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:21:59 by ymassiou          #+#    #+#             */
/*   Updated: 2024/02/24 21:19:01 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_do(int fd, int *p_fds, char **command1, char **env)
{
	dup2(fd, 0);
	close(fd);
	close(p_fds[0]);
	dup2(p_fds[1], 1);
	close(p_fds[1]);
	if (execve(command1[0], command1, env) != -1)
		perror("NIGGA");

}

void	child2_do(int fd, int *p_fds, char **command2, char **env)
{
	close(p_fds[1]);
	dup2(p_fds[0], 0);
	close(p_fds[0]);
	dup2(fd ,1);
	close(fd);
	execve(command2[0], command2, env);
}

int	valid_file(char *path, int in_or_out)
{
	int fd;

	if (in_or_out == 0)
		fd = open(path, O_RDONLY, 0666);
	else
		fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	return (fd);
}

int main (int ac, char **av, char **env)
{
	char **command1;
	char **command2;
	char *path;
	char **potential_path;
	int end[2];
	int id1;
	int id2;
	int fd1;
	int fd2;

	if (ac < 5)
		exit(EXIT_FAILURE);
	fd1 = valid_file(av[1], 0);
	fd2 = valid_file(av[4], 1);
	if (fd1 == -1 || fd2 == -1)
	{
		perror(av[1]);
		exit(EXIT_FAILURE);
	}
	command1 = ft_split(av[2], ' ');
	command2 = ft_split(av[3], ' ');
	path = extract_path(env);
	potential_path = ft_split(path, ':');
	command1[0] = check_command(command1[0], potential_path);
	command2[0] = check_command(command2[0], potential_path);
	if (!command1[0] || !command2[0])
		exit(EXIT_FAILURE);
	//free(paths); TODO++++++++
	if (pipe(end) == -1)
		exit(EXIT_FAILURE);
	id1 = fork();
	if (id1 == -1)
		exit(EXIT_FAILURE);
	if (!id1)
		child1_do(fd1, end, command1, env);
	id2 = fork();
	if (id2 == -1)
		exit(EXIT_FAILURE);
	if (!id2)
		child2_do(fd2, end, command2, env);
	close(end[1]);
	close(end[0]);
	close(fd1);
	close(fd2);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
	return (0);
}
// dup2(old, new);
/*
what ever 'old' is connected to duplicate it and make 'new' connected to it too
so when i use 'new' it will take to me to stream that 'old' points to too
*/
