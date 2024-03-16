/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:20:24 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/15 22:24:36 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	main(int ac, char **av, char **env)
{
	t_process	data;

	if (ac != 5)
	{
		ft_putstr_fd("Wrong number of argumens!\n", 2);
		ft_putstr_fd("->Usage: ./pipex INFILE cmd1 cmd2 OUTFILE\n", 2);
		exit(EXIT_FAILURE);
	}
	check_env(&data, env);
	check_potential_path(&data);
	pipex_start(&data, av, ac);
	pipex_end(&data, av, ac);
	return (0);
}
