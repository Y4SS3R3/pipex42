/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:24:22 by ymassiou          #+#    #+#             */
/*   Updated: 2024/02/21 09:28:45 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
