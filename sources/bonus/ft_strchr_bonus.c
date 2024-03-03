/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:21:01 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/02 15:41:04 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
