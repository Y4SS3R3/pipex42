/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:15:38 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/16 01:00:05 by ymassiou         ###   ########.fr       */
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
	pass_command(data, first_command);
}

void	pipex_start(t_process *data, char **av, int ac)
{
	if (pipe(data->end) == -1)
		return (close(data->out_fd), error_iv("Pipe() problem.\n", data));
	data->in_fd = valid_file(av[1], 0);
	data->out_fd = valid_file(av[ac - 1], 1);
	if (data->out_fd == -1)
		custom_error1("File cannot be opened.\n", data);
	data->pid = fork();
	if (data->pid == -1)
	{
		close(data->out_fd);
		custom_error1("Fork() problem.\n", data);
	}
	if (data->pid == 0)
		first_child(data, av[2]);
	else
	{
		close(data->end[1]);
		if (dup2_more(data->end[0], 0) == -1)
			error_iv("Unexpected error[3].\n", data);
		if (data->in_fd != -1)
			close(data->in_fd);
	}
}

void	pipex_end(t_process *data, char **av, int ac)
{
	char	*tmp;
	int		flag;

	flag = 0;
	data->command = ft_splitws(av[ac - 2]);
	tmp = data->command[0];
	data->command[0] = check_command(data->command[0],
			data->potential_path, &flag);
	if (ft_strcmp(data->command[0], tmp) > 0 && flag != 0)
		free(tmp);
	data->pid = fork();
	if (data->pid == -1)
		custom_error2("Fork() error.\n", data);
	if (data->pid == 0)
	{
		if (data->command[0] == NULL)
			custom_error2("Command not found.\n", data);
		last_child(data);
	}
	else
		finish_it(data);
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
			custom_error5(data, "Fork() problem.\n");
		if (data->pid == 0)
			pass_command(data, av[index]);
		else
		{
			close(data->end[1]);
			if (dup2_more(data->end[0], 0) == -1)
			{
				close(data->out_fd);
				error_iv("Unexpected error[3].\n", data);
			}
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
	pipex_end(&data, av, ac);
	return (0);
}
