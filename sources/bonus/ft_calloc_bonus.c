/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:04:23 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/02 16:05:29 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
