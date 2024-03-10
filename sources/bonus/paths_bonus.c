/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:08:49 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/10 13:46:50 by ymassiou         ###   ########.fr       */
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
	return (NULL);
}

char	*check_command(char *command, char **paths, int *flag)
{
	char	*result;
	int		i;

	i = 0;
	if (command == NULL)
		return (NULL);
	result = NULL;
	if (ft_strchr(command, '/') == NULL)
	{
		*flag = 1;
		return (create_path(paths, command));
	}
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
