/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:08:59 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/10 11:10:40 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = NULL;
	if ((count * size) > SIZE_T_MAX)
		return (NULL);
	result = malloc(count * size);
	if (result == NULL)
		return (NULL);
	return (ft_memset(result, 0, count * size));
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmpd;
	unsigned char	*tmps;

	if (src == NULL && dst == NULL)
		return (dst);
	i = 0;
	tmpd = (unsigned char *)dst;
	tmps = (unsigned char *)src;
	while (i < n)
	{
		tmpd[i] = tmps[i];
		i++;
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char *)b;
	i = 0;
	while (i < len)
		tmp[i++] = (unsigned char)c;
	return (b);
}

char	*ft_strchr(const char *haystack, int needle)
{
	size_t	i;

	i = 0;
	if (haystack == NULL)
		return (NULL);
	while (haystack[i])
	{
		if (haystack[i] == (char)needle)
			return ((char *)&haystack[i]);
		i++;
	}
	if (haystack[i] == (char)needle)
		return ((char *)&haystack[i]);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	size1;
	char	*tmp;

	tmp = NULL;
	size1 = ft_strlen(s1) + 1;
	tmp = (char *)malloc(size1);
	if (tmp == NULL)
		return (NULL);
	return (ft_memcpy(tmp, s1, size1));
}
