/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:15:38 by ymassiou          #+#    #+#             */
/*   Updated: 2024/02/28 18:04:06 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	heredocing_time(int ac, char *limiter)
{
	int		fd;
	char	*line = NULL;
	size_t	len = 0;
	ssize_t	read;

	if (ac < 6)
		exit(EXIT_FAILURE);
	fd = open("here_doc", O_CREAT | O_TRUNC | O_RDWR, 0666);
	while (1)
	{
		write(1, "heredoc> ", 9);
		read = getline(&line, &len, stdin);
		if (ft_strcmp(limiter, ft_substr(line, 0, ft_strlen(line) - 1)) == 0)
			break;
		write(fd, line, ft_strlen(line));
	}
	dup2(fd, 0);
	close(fd);
}

void ff()
{
	system("lsof -c pipo");
}

int main(int ac, char **av, char **env)
{
	char		**potential_path;
	int			end[2];
	int			in_fd;
	int			out_fd;
	int			index;
	int			pid;
	char		**command;

	atexit(ff);
	if (ac < 5)
		exit(EXIT_FAILURE);
	potential_path = ft_split(extract_path(env), ':');
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		index = 3;
		out_fd = valid_file(av[ac - 1], 2);
		heredocing_time(ac, av[2]);
	}
	else
	{
		in_fd = valid_file(av[1], 0);
		out_fd = valid_file(av[ac - 1], 1);
		dup2(in_fd ,0);
		close(in_fd);
		index = 2;
	}
	while (index < ac - 2)
	{
		if (pipe(end) == -1)
			errno_protocol();
		pid = fork();
		if (pid == -1)
			errno_protocol();
		if (pid == 0)
		{
			close(end[0]);
			dup2(end[1], 1);
			close(end[1]);
			command = ft_split(av[index], ' ');
			command[0] = check_command(command[0], potential_path);
			execve(command[0], command, env);
		}
		else
		{
			close(end[1]);
			dup2(end[0], 0);
			close(end[0]);
		}
		index++;
	}
	command = ft_split(av[ac - 2], ' ');
	command[0] = check_command(command[0], potential_path);
	pid = fork();
	if (pid == -1)
		errno_protocol();
	if(pid == 0)
	{
		dup2(out_fd, 1);
		close(out_fd);
		execve(command[0], command, env);
	}
	close(0);
	close(out_fd);
	while (wait(NULL) != -1);
	exit (0);
}
