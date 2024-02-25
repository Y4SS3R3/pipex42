/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:21:53 by ymassiou          #+#    #+#             */
/*   Updated: 2024/02/25 20:39:48 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1_do(char *path, int *p_fds, char **command1, char **env)
{
	int	fd;

	fd = valid_file(path, 0);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, 0);
	close(fd);
	close(p_fds[0]);
	dup2(p_fds[1], 1);
	close(p_fds[1]);
	if (execve(command1[0], command1, env) == -1)
		exit(EXIT_FAILURE);
}

void	child2_do(char *path, int *p_fds, char **command2, char **env)
{
	int	fd;

	fd = valid_file(path, 1);
	if (fd == -1)
		exit(EXIT_FAILURE);
	close(p_fds[1]);
	dup2(p_fds[0], 0);
	close(p_fds[0]);
	dup2(fd ,1);
	close(fd);
	if (execve(command2[0], command2, env) == -1)
		exit(EXIT_FAILURE);
}

char *create_path(char **paths, char *command)
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
			return(NULL);
		if (access(result, X_OK) != -1)
			break;
		free(result);
		i++;
	}
	free(command);
	return (result);
}

char *check_command(char *command, char **paths)
{
	char *result;
	int i;

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
			return(NULL);
		}
		else
			result = command;
	}
	return (result);
}

char *get_env(char **env)
{
	while(*env)
	{
		if (ft_strnstr(*env, "PATH", 5) != NULL)
			return (*env);
		env++;
	}
	return (NULL);
}

char *extract_path(char **env)
{
	char *str;

	str = get_env(env);
	if (str == NULL)
		exit(EXIT_FAILURE);
	while (*str != '=')
		str++;
	return (str + 1);
}

int	valid_file(char *path, int in_or_out)
{
	int fd;

	if (in_or_out == 0)
		fd = open(path, O_RDONLY, 0666);
	else
		fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	return (fd);
}
