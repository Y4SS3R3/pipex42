/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:44:57 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/17 03:18:07 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
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

void	first_child(t_process *data, char *first_command)
{
	if (data->in_fd == -1)
	{
		close(data->end[0]);
		close(data->end[1]);
		close(data->out_fd);
		error_iv("The infile does not exist.\n", data);
	}
	if (dup2_more(data->in_fd, 0) == -1)
	{
		close(data->end[0]);
		close(data->end[1]);
		close(data->out_fd);
		error_iv("Dup2() problem.\n", data);
	}
	pass_command(data, first_command);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	if (fd >= 0)
	{
		while (*s)
			write(fd, s++, 1);
	}
}
