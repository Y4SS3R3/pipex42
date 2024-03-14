/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:52:24 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/14 12:23:19 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*update_size(int old_size, char *old_buffer, int *allocate)
{
	char	*tmp;
	char	*new_buffer;

	*allocate = old_size + 100;
	new_buffer = malloc(*allocate);
	tmp = old_buffer;
	if (new_buffer == NULL)
		return (NULL);
	new_buffer = ft_memcpy(new_buffer, old_buffer, old_size);
	old_buffer = new_buffer;
	free(tmp);
	return (old_buffer);
}

static char	*fill_buffer(char *buffer, int *readed, int *i)
{
	int		allocate;
	char	c;

	allocate = 10000;
	*readed = read(0, &c, 1);
	while (*readed && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[*i] = c;
		(*i)++;
		if (*i > allocate - 1)
		{
			buffer = update_size(*i, buffer, &allocate);
			if (buffer == NULL)
				return (buffer);
		}
		*readed = read(0, &c, 1);
	}
	return (buffer);
}

static int	check_eof(int bytes, char *to_free)
{
	if (bytes == 0)
		free(to_free);
	return (bytes);
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		readed;
	int		i;
	int		allocate;

	i = 0;
	allocate = 10000;
	readed = 0;
	buffer = (char *)malloc(allocate);
	if (buffer == NULL)
		return (-1);
	buffer = fill_buffer(buffer, &readed, &i);
	if (buffer == NULL)
		return (-1);
	if (check_eof(readed, buffer) == 0)
		return (0);
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	return (readed);
}
