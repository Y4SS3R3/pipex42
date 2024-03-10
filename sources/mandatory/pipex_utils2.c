/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:22:43 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/10 16:53:17 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	ft_free(potential_path, get_length(potential_path));
	ft_free(command1, get_length(command1));
	ft_free(command2, get_length(command2));
}

int	get_length(char **array)
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
