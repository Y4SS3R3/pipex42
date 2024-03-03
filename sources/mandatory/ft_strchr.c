/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:21:01 by ymassiou          #+#    #+#             */
/*   Updated: 2024/02/28 21:43:55 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
