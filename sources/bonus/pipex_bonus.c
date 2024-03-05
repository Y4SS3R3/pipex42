/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:15:38 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/05 17:46:09 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	arg_error()
{
	write(2, "	->Programm needs 5 arguments at least.\n", 40);
	exit(EXIT_FAILURE);
}

void	check_potential_path(t_process *data)
{
	char *res;

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

// protect from unset PATH;

void	pipex_end(t_process *data, char **av, int out_fd, int ac)
{
	char	*tmp;

	data->command = ft_split(av[ac - 2], ' ');
	tmp = data->command[0];
	data->command[0] = check_command(data->command[0], data->potential_path);
	free(tmp);
	data->pid = fork_plus();
	if(data->pid == 0)
		last_child(data, out_fd);
	close(0);
	close(out_fd);
	while (wait(NULL) != -1);
	ft_free(data->potential_path, get_lenght(data->potential_path));
	ft_free(data->command, get_lenght(data->command));
}

void	pipex_middle(int index, int ac,t_process *data, char **av)
{
	while (index < ac - 2)
	{
		if (pipe(data->end) == -1)
			errno_protocol();
		data->pid = fork_plus();
		if (data->pid == 0)
			pass_command(data, av[index]);
		else
		{
			close(data->end[1]);
			dup2(data->end[0], 0);
			close(data->end[0]);
		}
		index++;
	}
}

void	fill_heredoc(char *limiter, int hrdc_fd)
{
	int		read;
	char	*line;
	char	*tmp;

	line = NULL;
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		read = get_next_line(&line);
		if (read == 0)
			return ;
		/*double free when ^D at the first line*/
		if (read == -1)
		{
			free(line);
			write(2, "Problem reading from the here_doc file.\n", 40);
			exit(EXIT_FAILURE);
		}
		tmp = ft_substr(line, 0, ft_strlen(line) - 1);
		if (tmp == NULL)
		{
			free(line);
			write(2, "Malloc() error.\n", 16);
			exit(EXIT_FAILURE);
		}
		if (ft_strcmp(limiter, tmp) == 0)
		{
			free(line);
			free(tmp);
			return ;
		}
		if (write(hrdc_fd, line, ft_strlen(line)) == -1)
		{
			free(tmp);
			free(line);
			write(2, "Write() error.\n", 15);
			exit(EXIT_FAILURE);
		}
		if (tmp)
			free(tmp);
		if (line)
			free(line);
	}
}

char *randomize_file_name(void)
{
	int	i;
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

void	heredocing_time(int ac, char *limiter)
{
	int		fd;
	char	*name;

	if (ac < 6)
	{
		write(2, "	->here_doc needs 6 arguments at least.\n", 40);
		write(2, "	->Usage: ./pipex_bonus here_doc LIMITER cmd1 cmd2 cmd3 ... OUTFILE.\n", 69);
		exit(EXIT_FAILURE);
	}
	name = randomize_file_name();
	fd = open(name ,O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
	{
		free(name);
		write(2, "Failure while opening here_doc file.\n", 37);
		exit(EXIT_FAILURE);
	}
	fill_heredoc(limiter, fd);
	if (close(fd) == -1)
	{
		free(name);
		write(2, "Close() failed.\n", 14);
		exit(EXIT_FAILURE);
	}
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		free(name);
		write(2, "Open() failed.\n", 15);
		exit(EXIT_FAILURE);
	}
	if (dup2_more(fd, 0) == -1)
	{
		free(name);
		write(2, "Unexpected error[1].\n", 18);
		exit(EXIT_FAILURE);
	}
	if (unlink(name) == -1)
	{
		free(name);
		write(2, "Problem unlinking the file.\n", 28);
		exit(EXIT_FAILURE);
	}
	free(name);
}

void ff()
{
	system("leaks pipex_bonus");
}

int main(int ac, char **av, char **env)
{
	int			in_fd;
	int			out_fd;
	int			index;
	t_process	data;

	atexit(ff);
	if (ac < 5 && ft_strcmp(av[1], "here_doc") != 0)
		arg_error();
	check_env(&data, env);
	check_potential_path(&data);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		index = 3;
		out_fd = valid_file(av[ac - 1], 2);
		heredocing_time(ac, av[2]);
	}
	else
	{
		index = 2;
		in_fd = valid_file(av[1], 0);
		out_fd = valid_file(av[ac - 1], 1);
		dup2_more(in_fd, 0);
	}
	pipex_middle(index, ac, &data, av);
	pipex_end(&data, av, out_fd, ac);
	return(0);
}
