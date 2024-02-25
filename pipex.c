/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:21:59 by ymassiou          #+#    #+#             */
/*   Updated: 2024/02/25 20:44:00 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void lol()
{
	system("leaks pipex");
}

void	execute_child_1(char *path1, char **command1, int *end, char **env, id)
{
	int	id;

	id = fork();
	if (id == -1)
		exit(EXIT_FAILURE);
	if (!id)
		child2_do(path1, end, command1, env);
}

void	execute_child_2(char *path2, char **command2, int *end, char **env, id)
{
	int	id;

	id = fork();
	if (id == -1)
		exit(EXIT_FAILURE);
	if (!id)
		child1_do(path2, end, command2, env);
}

int	get_lenght(char **array)
{
	int	i;

	i = 0;
	while (*array)
	{
		i++;
		array++;
	}
	printf(">> %d\n", i);
	return (i);
}

void	end_it(int *end, char **potential_path, char **command1, char **command2)
{
	close(end[1]);
	close(end[0]);
	ft_free(potential_path, get_lenght(potential_path));
	ft_free(command1, get_lenght(command1));
	ft_free(command2, get_lenght(command2));
}

int main (int ac, char **av, char **env)
{
	char **command1;
	char **command2;
	char *tmp;
	char **potential_path;
	int end[2];
	int id1;
	int id2;

	if (ac < 5)
		exit(EXIT_FAILURE);
	command1 = ft_split(av[2], ' ');
	command2 = ft_split(av[3], ' ');
	potential_path = ft_split(extract_path(env), ':');
	tmp = command1[0];
	command1[0] = check_command(command1[0], potential_path);
	command2[0] = check_command(command2[0], potential_path);
	if (!command1[0] || !command2[0])
		exit(EXIT_FAILURE);
	if (pipe(end) == -1)
		exit(EXIT_FAILURE);
	execute_child_1(av[1], command1, end, env, id1);
	execute_child_2(av[4], command2, end, env, id2);
	end_it(end, potential_path, command1, command2);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
	atexit(lol);
	return (0);
}
// dup2(old, new);
/*
what ever 'old' is connected to duplicate it and make 'new' connected to it too
so when i use 'new' it will take to me to stream that 'old' points to too
*/
