/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:11:03 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/10 11:53:38 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(""));
	if (s2 == NULL)
		return (ft_strdup(s1));
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;
	size_t	dlen;
	size_t	i;

	i = 0;
	slen = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (slen);
	while (dst[i])
		i++;
	dlen = i;
	if (dstsize <= dlen)
		return (dstsize + slen);
	if (dlen + slen < dstsize)
		ft_memcpy(&dst[i], src, slen + 1);
	else
	{
		ft_memcpy(&dst[i], src, dstsize - dlen - 1);
		dst[dstsize - 1] = 0;
	}
	return (dlen + slen);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
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
