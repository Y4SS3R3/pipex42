/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:20 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/10 22:36:56 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_v(char *message, t_process *data)
{
	ft_putstr_fd(message, 2);
	ft_free(data->potential_path, get_length(data->potential_path));
	ft_free(data->command, get_length(data->command));
	exit(EXIT_FAILURE);
}

void	error_iv(char *message, t_process *data)
{
	ft_putstr_fd(message, 2);
	ft_free(data->potential_path, get_length(data->potential_path));
	exit(EXIT_FAILURE);
}

void	error_iii(char *message, char *to_free1,
		t_process *data, char *to_free2)
{
	free(to_free1);
	error_ii(message, data, to_free2);
}

void	error_ii(char *message, t_process *data, char *to_free)
{
	free(to_free);
	ft_putstr_fd(message, 2);
	ft_free(data->potential_path, get_length(data->potential_path));
	exit(EXIT_FAILURE);
}