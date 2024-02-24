/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:21:53 by ymassiou          #+#    #+#             */
/*   Updated: 2024/02/24 14:27:22 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *create_path(char **paths, char *command)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (paths[i])
	{
		result = ft_strjoin("/", command);
		result = ft_strjoin(paths[i], result);
		if (result == NULL)
			return(NULL);
		if (access(result, X_OK) != -1)
			break;
		free(result);
		i++;
	}
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
