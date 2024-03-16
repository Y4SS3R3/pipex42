/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:41:13 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/16 22:19:13 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	custom_error1(char *message, t_process *data)
{
	close(data->end[0]);
	close(data->end[1]);
	close(data->in_fd);
	error_iv(message, data);
}

void	custom_error2(char *message, t_process *data)
{
	close(data->out_fd);
	error_v(message, data);
}

void	custom_error6(t_process *data, char *message)
{
	close(data->end[0]);
	close(data->end[1]);
	close(data->out_fd);
	close(data->out_fd);
	error_iv(message, data);
}
