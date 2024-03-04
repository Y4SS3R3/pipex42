/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:21:59 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/03 22:35:22 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child(t_process *child, int *end, char **env,
		void (*child_do)(char *, int *, char **, char **))
{
	child->pid = fork();
	if (child->pid == -1)
		errno_protocol();
	if (!child->pid)
		child_do(child->path, end, child->command, env);
}

int	main(int ac, char **av, char **env)
{
	char		**potential_path;
	int			end[2];
	t_process	child1;
	t_process	child2;

	if (ac < 5)
		exit(EXIT_FAILURE);
	child1.path = av[1];
	child2.path = av[4];
	child1.command = ft_split(av[2], ' ');
	child2.command = ft_split(av[3], ' ');
	potential_path = ft_split(extract_path(env), ':');
	child1.command[0] = check_command(child1.command[0], potential_path);
	child2.command[0] = check_command(child2.command[0], potential_path);
	if (pipe(end) == -1)
		errno_protocol();
	execute_child(&child1, end, env, child1_do);
	execute_child(&child2, end, env, child2_do);
	end_it(end, potential_path, child1.command, child2.command);
	while (wait(NULL) != -1)
		;
	return (0);
}
// dup2(old, new);
/*
what ever 'old' is connected to duplicate it and make 'new' connected to it too
so when i use 'new' it will take to me to stream that 'old' points to too
*/
