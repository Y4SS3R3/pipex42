/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:15:38 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/08 12:42:20 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	arg_error(void)
{
	write(2, "	->Programm needs 5 arguments at least.\n", 40);
	exit(EXIT_FAILURE);
}

void	check_potential_path(t_process *data)
{
	char	*res;

	res = extract_path(data->envp);
	if (res == NULL)
	{
		write(2, "PATH variable not found\n", 24);
		exit(EXIT_FAILURE);
	}
	data->potential_path = ft_split(res, ':');
}

void	check_env(t_process *data, char **env)
{
	if (*env == NULL)
	{
		write(2, "Error in environment\n", 21);
		exit(EXIT_FAILURE);
	}
	data->envp = env;
}

void	error_iv(char *message, t_process *data)
{
	ft_putstr_fd(message, 2);
	ft_free(data->potential_path, get_lenght(data->potential_path));
	exit(EXIT_FAILURE);
}

void	first_child(int in_fd, t_process *data, char *first_command)
{
	if (in_fd == -1)
	{
		close(data->end[0]);
		close(data->end[1]);
		error_iv("The infile does not exist.\n", data);
	}
	if (dup2_more(in_fd, 0) == -1)
		error_iv("Dup2() problem.\n", data);
	pass_command(data, first_command);
}

void	pipex_start(t_process *data, char **av, int ac, int *out_fd)
{
	int	in_fd;

	if (pipe(data->end) == -1)
		error_iv("Pipe() problem.\n", data);
	in_fd = valid_file(av[1], 0);
	*out_fd = valid_file(av[ac - 1], 1);
	if (*out_fd == -1)
		error_iv("File cannot be opened.\n", data);
	data->pid = fork();
	if (data->pid == -1)
		error_iv("Fork() problem.\n", data);
	if (data->pid == 0)
		first_child(in_fd, data, av[2]);
	else
	{
		if (close(data->end[1]) == -1)
			error_iv("Close(1) problem.\n", data);
		if (dup2_more(data->end[0], 0) == -1)
			error_iv("Unexpected error[3].\n", data);
		if (in_fd != -1 && close(in_fd) == -1)
			error_iv("Close(2) problem.\n", data);
	}
}

void	error_v(char *message, t_process *data)
{
	ft_putstr_fd(message, 2);
	ft_free(data->potential_path, get_lenght(data->potential_path));
	ft_free(data->command, get_lenght(data->command));
	exit(EXIT_FAILURE);
}

void	close_both(t_process *data, int out_fd)
{
	if (close(0) == -1)
		error_v("Close() error.\n", data);
	if (close(out_fd) == -1)
		error_v("Close() error.\n", data);
}

void	last_free(t_process *data)
{
	ft_free(data->potential_path, get_lenght(data->potential_path));
	ft_free(data->command, get_lenght(data->command));
}

void	pipex_end(t_process *data, char **av, int out_fd, int ac)
{
	char	*tmp;

	data->command = ft_split(av[ac - 2], ' ');
	tmp = data->command[0];
	data->command[0] = check_command(data->command[0], data->potential_path);
	if (ft_strcmp(data->command[0], tmp) != 0)
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
	{
		close_both(data, out_fd);
		while (wait(NULL) != -1)
			;
		last_free(data);
	}
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
			error_iv("Fork() problem.\n", data);
		if (data->pid == 0)
			pass_command(data, av[index]);
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

void	error_ii(char *message, t_process *data, char *to_free)
{
	free(to_free);
	ft_putstr_fd(message, 2);
	ft_free(data->potential_path, get_lenght(data->potential_path));
	exit(EXIT_FAILURE);
}

void	error_iii(char *message, char *to_free1,
		t_process *data, char *to_free2)
{
	free(to_free1);
	error_ii(message, data, to_free2);
}

int	find_limiter(char *limiter, char *line, char *tmp)
{
	if (ft_strcmp(limiter, tmp) == 0)
	{
		free(line);
		free(tmp);
		return (0);
	}
	return (1);
}

void	fill_heredoc(char *limiter, int hrdc_fd, t_process *data)
{
	int		read;
	char	*line;
	char	*tmp;

	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		read = get_next_line(&line);
		if (read == 0)
		{
			write(1, "\n", 1);
			return ;
		}
		if (read == -1)
			error_ii("Problem reading from the here_doc file.\n", data, line);
		tmp = ft_substr(line, 0, ft_strlen(line) - 1);
		if (tmp == NULL)
			error_ii("Malloc() error.\n", data, line);
		if (find_limiter(limiter, line, tmp) == 0)
			return ;
		if (write(hrdc_fd, line, ft_strlen(line)) == -1)
			error_iii("Write() error.\n", tmp, data, line);
		free(tmp);
		free(line);
	}
}

char	*randomize_file_name(void)
{
	int		i;
	char	*name;
	char	*tmp;

	i = 0;
	name = NULL;
	while (i < INT_MAX)
	{
		name = ft_itoa(i);
		tmp = name;
		name = ft_strjoin("/tmp/", name);
		free(tmp);
		if (access(name, F_OK) == -1)
			return (name);
		free(name);
		i++;
	}
	return (NULL);
}

void	hrdc_arg_error(void)
{
	char	*m;

	m = "->Usage: ./pipex_bonus here_doc LIMITER cmd1 cmd2 cmd3 ... OUTFILE.\n";
	write(2, "->here_doc needs 6 arguments at least.\n", 40);
	write(2, m, 69);
	exit(EXIT_FAILURE);
}

void	error_i(char *message, t_process *data, char *to_free)
{
	free(to_free);
	ft_putstr_fd(message, 2);
	ft_free(data->potential_path, get_lenght(data->potential_path));
	exit(EXIT_FAILURE);
}

void	heredocing_time(int ac, char *limiter, t_process *data)
{
	int		fd;
	char	*name;

	if (ac < 6)
		hrdc_arg_error();
	name = randomize_file_name();
	fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		error_i("Failure while opening here_doc file.\n", data, name);
	fill_heredoc(limiter, fd, data);
	if (close(fd) == -1)
		error_i("Close() failed.\n", data, name);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		error_i("Open() failed.\n", data, name);
	if (dup2_more(fd, 0) == -1)
		error_i("Unexpected error[1].\n", data, name);
	if (unlink(name) == -1)
		error_i("Problem unlinking the file.\n", data, name);
	free(name);
}

int	main(int ac, char **av, char **env)
{
	int			out_fd;
	int			index;
	t_process	data;

	if (ac < 5 && ft_strcmp(av[1], "here_doc") != 0)
		arg_error();
	check_env(&data, env);
	check_potential_path(&data);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		index = 3;
		out_fd = valid_file(av[ac - 1], 2);
		if (out_fd == -1)
		{
			write(2, "Problem opening the outfile when here_doc is used\n", 50);
			ft_free(data.potential_path, get_lenght(data.potential_path));
			exit(EXIT_FAILURE);
		}
		heredocing_time(ac, av[2], &data);
	}
	else
		pipex_start(&data, av, ac, &out_fd);
	pipex_middle(ac, &data, av);
	pipex_end(&data, av, out_fd, ac);
	return (0);
}
