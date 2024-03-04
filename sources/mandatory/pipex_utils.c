/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:21:53 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/04 01:20:50 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	free(command);
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
