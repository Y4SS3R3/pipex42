/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:06:52 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/08 16:44:15 by ymassiou         ###   ########.fr       */
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
	int		readed;
	int		i;
	char	c;

	i = 0;
	readed = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	readed = read(0, &c, 1);
	while (readed && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		readed = read(0, &c, 1);
	}
	if (check_eof(readed, buffer) == 0)
		return (0);
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	return (readed);
}
