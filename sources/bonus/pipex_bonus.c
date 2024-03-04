/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:15:38 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/04 01:13:12 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	fill_heredoc(char *limiter, int hrdc_fd)
{
    int		read;
    char	*line;
    char	*tmp;

    read = 1;
    line = NULL;
    while (read > 0)
    {
        write(1, "pipe heredoc> ", 14);
        read = get_next_line(&line);
        if (read == 0)
            return (0);
        tmp = ft_substr(line, 0, ft_strlen(line) - 1);
        if (ft_strcmp(limiter, tmp) == 0)
        {
            free(line);
            free(tmp);
            line = NULL;
            return (0);
        }
        write(hrdc_fd, line, ft_strlen(line));
        if (tmp)
            free(tmp);
        if (line)
            free(line);
    }
    if (read == -1)
        return (-1);
    return (0);
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
	int		read;
	char	*name;

	if (ac < 6)
		exit(EXIT_FAILURE);
	name = randomize_file_name();
	fd = open(name ,O_CREAT | O_TRUNC | O_RDWR, 0666);
	read = 1;
	fill_heredoc(limiter, fd);
	close(fd);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2_more(fd, 0);
	unlink(name);
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

	if (ac < 5)
		exit(EXIT_FAILURE);
	data.envp = env;
	data.potential_path = ft_split(extract_path(data.envp), ':');
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
