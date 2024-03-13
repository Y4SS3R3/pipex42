/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:21:53 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/13 11:24:29 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		fd = open(path, O_RDONLY, 0644);
	else if (in_or_out == 1)
		fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd);
}

void	finish_it(t_process *data)
{
	close(data->out_fd);
	while (wait(NULL) != -1)
		;
	last_free(data);
}
