/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:47:16 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/17 03:47:56 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*gen_word(const char *s, char c)
{
	size_t	i;
	char	*result;

	result = NULL;
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	result = ft_substr(s, 0, i);
	return (result);
}

void	*ft_free(char **to_free, size_t elements, int flag)
{
	size_t	i;

	i = flag;
	if (i == 1)
	{
		while (to_free[i] != NULL)
		{
			free(to_free[i]);
			i++;
		}
	}
	else
	{
		while (i < elements)
		{
			free(to_free[i]);
			i++;
		}
	}
	free(to_free);
	return (NULL);
}

static int	words_count(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
			count++;
		i++;
	}
	return (count);
}

/*
handle tabs
*/

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**result;
	size_t	j;

	if (s == NULL)
		return (NULL);
	words = words_count(s, c);
	result = NULL;
	j = 0;
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (*s && words--)
	{
		while (*s == c && *s)
			s++;
		result[j] = gen_word(s, c);
		if (result[j] == NULL)
			return (ft_free(result, j, 0));
		j++;
		while (*s != c && *s)
			s++;
	}
	result[j] = 0;
	return (result);
}
