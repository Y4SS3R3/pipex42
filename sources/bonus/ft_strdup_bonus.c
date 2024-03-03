/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:24:22 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/02 15:41:01 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
