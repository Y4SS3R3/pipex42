/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:52:24 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/13 14:47:31 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_eof(int bytes, char *to_free)
{
	if (bytes == 0)
		free(to_free);
	return (bytes);
}

int	get_next_line(char **line)
{
	char	*buffer;
	char	*buffer_more;
	int		readed;
	int		i;
	int		allocate;
	char	c;

	i = 0;
	allocate = 10000;
	readed = 0;
	buffer = (char *)malloc(allocate);
	if (buffer == NULL)
		return (-1);
	readed = read(0, &c, 1);
	while (readed && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		if (i > allocate - 1)
		{
			allocate = i + 1000;
			buffer_more = malloc(allocate);
			if (buffer_more == NULL)
				return (-1);
			buffer_more = ft_memcpy(buffer_more, buffer, i);
			// free(buffer);
		}
		readed = read(0, &c, 1);
	}
	if (check_eof(readed, buffer) == 0)
		return (0);
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	return (readed);
}
