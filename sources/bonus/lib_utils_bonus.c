/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:12:23 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/08 20:13:59 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
