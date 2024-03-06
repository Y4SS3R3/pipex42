/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:21:53 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/06 12:56:25 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_child(t_process *data, int out_fd)
{
	if (dup2_more(out_fd, 1) == -1)
	{
		write(2, "Unexpected error[4].\n", 21);
		ft_free(data->potential_path, get_lenght(data->potential_path));
		ft_free(data->command, get_lenght(data->command));
		exit(EXIT_FAILURE);
	}
	if (execve(data->command[0], data->command, data->envp) == -1)
	{
		write(2, "Execve() error.\n", 16);
		ft_free(data->potential_path, get_lenght(data->potential_path));
		ft_free(data->command, get_lenght(data->command));
		exit(EXIT_FAILURE);
	}
}

void	pass_command(t_process *data, char *command_av)
{
	if (close(data->end[0]) == -1)
	{
		write(1, "Close() problem.\n", 17);
		ft_free(data->potential_path, get_lenght(data->potential_path));
		exit(EXIT_FAILURE);
	}
	if (dup2_more(data->end[1], 1) == -1)
	{
		write(1, "Dup2() problem.\n", 17);
		ft_free(data->potential_path, get_lenght(data->potential_path));
		exit(EXIT_FAILURE);
	}
	data->command = ft_split(command_av, ' ');
	data->command[0] = check_command(data->command[0], data->potential_path);
	if(data->command[0] == NULL)
	{
		write(2, "Command not found.\n", 19);
		ft_free(data->potential_path, get_lenght(data->potential_path));
		ft_free(data->command, get_lenght(data->command));
		exit(EXIT_FAILURE);
	}
	if (execve(data->command[0], data->command, data->envp) == -1)
	{
		write(1, "Execve() error.\n", 16);
		ft_free(data->potential_path, get_lenght(data->potential_path));
		ft_free(data->command, get_lenght(data->command));
		exit(EXIT_FAILURE);
	}
}

int	dup2_more(int old, int new)
{
	int ret1;
	int ret2;

	ret1 = dup2(old, new);
	ret2 = close(old);
	if (ret1 == -1 || ret2 == -1)
		return (-1);
	return (0);
}


char	*create_path(char **paths, char *command)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 0;
	result = NULL;
	while (paths[i])
	{
		result = ft_strjoin("/", command);
		tmp = result;
		result = ft_strjoin(paths[i], result);
		free(tmp);
		if (result == NULL)
			return (NULL);
		if (access(result, X_OK) != -1)
			return (result);
		free(result);
		i++;
	}
	// free(command);
	return (NULL);
}

char	*check_command(char *command, char **paths)
{
	char	*result;
	int		i;

	i = 0;
	if (command == NULL)
		return (NULL);
	result = NULL;
	if (ft_strchr(command, '/') == NULL)
		return (create_path(paths, command));
	else
	{
		if (access(command, X_OK) == -1)
		{
			free(command);
			return (NULL);
		}
		else
			result = command;
	}
	return (result);
}

char	*get_env(char **env)
{
	while (*env)
	{
		if (ft_strnstr(*env, "PATH", 5) != NULL)
			return (*env);
		env++;
	}
	return (NULL);
}

char	*extract_path(char **env)
{
	char	*str;

	str = get_env(env);
	if (str == NULL)
		return (NULL);
	while (*str != '=')
		str++;
	return (str + 1);
}

int	valid_file(char *path, int in_or_out)
{
	int	fd;

	if (in_or_out == 0)
		fd = open(path, O_RDONLY, 0666);
	else if (in_or_out == 1)
		fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);
	return (fd);
}

size_t	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	end_it(int *end, char **potential_path,
	char **command1, char **command2)
{
	close(end[1]);
	close(end[0]);
	ft_free(potential_path, get_lenght(potential_path));
	ft_free(command1, get_lenght(command1));
	ft_free(command2, get_lenght(command2));
}

int	get_lenght(char **array)
{
	int	i;

	i = 0;
	while (*array)
	{
		i++;
		array++;
	}
	return (i);
}

void	errno_protocol(void)
{
	perror(NULL);
	exit(EXIT_FAILURE);
}
