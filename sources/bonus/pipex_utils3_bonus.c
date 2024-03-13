/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:33:51 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/13 12:15:28 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return ((char *)ft_calloc(1, 1));
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	i = 0;
	result = NULL;
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[len] = 0;
	return (result);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (len == 0 && haystack == NULL)
		return (NULL);
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && i + j < len && haystack[i + j])
			j++;
		if (needle[j] == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

void	*ft_free(char **to_free, size_t elements)
{
	size_t	i;

	i = 0;
	while (i < elements)
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
	return (NULL);
}
