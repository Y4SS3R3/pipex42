/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:15:38 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/11 15:50:01 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child(t_process *data, char *first_command)
{
	if (data->in_fd == -1)
	{
		close(data->end[0]);
		close(data->end[1]);
		close(data->out_fd);
		error_iv("The infile does not exist.\n", data);
	}
	if (dup2_more(data->in_fd, 0) == -1)
	{
		close(data->end[0]);
		close(data->end[1]);
		close(data->out_fd);
		error_iv("Dup2() problem.\n", data);
	}
	pass_command1(data, first_command);
}

void	pipex_start(t_process *data, char **av, int ac)
{
	if (pipe(data->end) == -1)
		return (close(data->out_fd), error_iv("Pipe() problem.\n", data));
	data->in_fd = valid_file(av[1], 0);
	data->out_fd = valid_file(av[ac - 1], 1);
	if (data->out_fd == -1)
	{
		close(data->end[0]);
		close(data->end[1]);
		close(data->in_fd);
		error_iv("File cannot be opened.\n", data); //close in_fd
	}
	data->pid = fork();
	if (data->pid == -1)
	{
		close(data->end[0]);
		close(data->end[1]);
		close(data->in_fd);
		close(data->out_fd);
		error_iv("Fork() problem.\n", data); // close in_fd and out_fd
	}
	if (data->pid == 0)
		first_child(data, av[2]);
	else
	{
		if (close(data->end[1]) == -1)
			error_iv("Close(1) problem.\n", data);
		if (dup2_more(data->end[0], 0) == -1)
			error_iv("Unexpected error[3].\n", data);
		if (data->in_fd != -1)
			error_iv("Close(2) problem.\n", data);
		close(data->in_fd);/*can turn into a problem later*/
	}
}

void	pipex_end(t_process *data, char **av, int out_fd, int ac)
{
	char	*tmp;
	int		flag;

	flag = 0;
	data->command = ft_split(av[ac - 2], ' ');
	tmp = data->command[0];
	data->command[0] = check_command(data->command[0],
			data->potential_path, &flag);
	if (ft_strcmp(data->command[0], tmp) > 0 && flag != 0)
		free(tmp);
	data->pid = fork();
	if (data->pid == -1)
		error_v("Fork() error.\n", data);
	if (data->pid == 0)
	{
		if (data->command[0] == NULL)
			error_v("Command not found.\n", data);
		last_child(data, out_fd);
	}
	else
		finish_it(data, out_fd);
}

void	pipex_middle(int ac, t_process *data, char **av)
{
	int	index;

	index = 3;
	while (index < ac - 2)
	{
		if (pipe(data->end) == -1)
			error_iv("Pipe() problem.\n", data);
		data->pid = fork();
		if (data->pid == -1)
		{
			close(data->end[0]);
			close(data->end[1]);
			close(data->out_fd);
			error_iv("Fork() problem.\n", data);
		}
		if (data->pid == 0)
			pass_command2(data, av[index]);// <-------------------
		else
		{
			if (close(data->end[1]) == -1)
				error_iv("Close() problem.\n", data);
			if (dup2_more(data->end[0], 0) == -1)
				error_iv("Unexpected error[3].\n", data);
		}
		index++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_process	data;

	if (ac < 5 && ft_strcmp(av[1], "here_doc") != 0)
		arg_error();
	check_env(&data, env);
	check_potential_path(&data);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		data.out_fd = valid_file(av[ac - 1], 2);
		if (data.out_fd == -1)
		{
			write(2, "Problem opening the outfile when here_doc is used\n", 50);
			ft_free(data.potential_path, get_length(data.potential_path));
			exit(EXIT_FAILURE);
		}
		heredocing_time(ac, av[2], &data);
	}
	else
		pipex_start(&data, av, ac);
	pipex_middle(ac, &data, av);
	pipex_end(&data, av, data.out_fd, ac);
	return (0);
}
