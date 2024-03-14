/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:21:59 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/14 12:27:36 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ff()
{
	system("lsof -c pipex");
}

void	execute_child(t_process *child, int *end, t_process *data,
		void (child_do)(t_process *, int *, t_process *))
{
	child->pid = fork();
	if (child->pid == -1)
		errno_protocol();
	if (!child->pid)
		child_do(child, end, data);
}

int	main(int ac, char **av, char **env)
{
	int			end[2];
	int			flag;
	t_process	child1;
	t_process	child2;
	t_process	data;

	atexit(ff);
	flag = 0;
	if (ac != 5)
	{
		ft_putstr_fd("Wrong number of argumens!\n", 2);
		ft_putstr_fd("->Usage: ./pipex INFILE cmd1 cmd2 OUTFILE\n", 2);
		exit(EXIT_FAILURE);
	}
	check_env(&data, env);
	check_potential_path(&data);
	child1.path = av[1];
	child2.path = av[4];
	child1.command = ft_splitws(av[2]);
	child2.command = ft_splitws(av[3]);
	child1.tmp = child1.command[0];
	child2.tmp = child2.command[0];
	child1.command[0] = check_command(child1.command[0],data.potential_path, &flag);
	child2.command[0] = check_command(child2.command[0], data.potential_path, &flag);
	if (ft_strcmp(child1.tmp, child1.command[0]) != 0 && flag != 0)
		free(child1.tmp);
	if (ft_strcmp(child2.tmp, child2.command[0]) != 0 && flag != 0)
		free(child2.tmp);
	if (pipe(end) == -1)
	{
		ft_putstr_fd("Problem with pipe().\n", 2);
		ft_free(data.potential_path, get_length(data.potential_path));
		ft_free(child1.command, get_length(child1.command));
		ft_free(child2.command, get_length(child2.command));
		exit(EXIT_FAILURE);
	}
	execute_child(&child1, end, &data, child1_do);
	execute_child(&child2, end, &data, child2_do);
	end_it(end, data.potential_path, child1.command, child2.command);
	while (wait(NULL) != -1)
		;
	return (0);
}
