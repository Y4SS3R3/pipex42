/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitws.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:47:16 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/17 03:23:49 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static char	*gen_word(const char *s)
{
	size_t	i;
	char	*result;

	result = NULL;
	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	result = ft_substr(s, 0, i);
	return (result);
}

static int	words_count(const char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]) && (s[i + 1] == 0 || ft_isspace(s[i + 1])))
			count++;
		i++;
	}
	return (count);
}

char	**ft_splitws(char const *s)
{
	size_t	words;
	char	**result;
	size_t	j;

	if (s == NULL)
		return (NULL);
	words = words_count(s);
	result = NULL;
	j = 0;
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (*s && words--)
	{
		while (ft_isspace(*s) && *s)
			s++;
		result[j] = gen_word(s);
		if (result[j] == NULL)
			return (ft_free(result, j, 0));
		j++;
		while (!ft_isspace(*s) && *s)
			s++;
	}
	result[j] = 0;
	return (result);
}
