#include "pipex.h"

char *check_command(char *command, char **paths)
{
	if ()
}

char *get_env(char **env)
{
	while(*env)
	{
		if (ft_strnstr(*env, "PATH", 5) != NULL)
			return (*env);
		env++;
	}
	return (NULL);
}

char *extract_path(char **env)
{
	char *str;

	str = get_env(env);
	if (str == NULL)
		exit(EXIT_FAILURE);
	while (*str != '=')
		str++;
	return (str + 1);
}

int main (int ac, char **av, char **env)
{
	char **command1;
	char **command2;
	char *binary2;
	char *binary1;
	char *path;
	char **potential_path;
	int end[2];
	int id1;
	int id2;

	// if (ac < 5)
	// 	exit(EXIT_FAILURE);
	// if (!valid_file(av[1]) || !valid_file(av[4]))
	// 	exit(EXIT_FAILURE);
	command1 = ft_split(av[2], ' ');
	command2 = ft_split(av[3], ' ');
	path = extract_path(env);
	potential_path = ft_split(path, ':');
	binary1 = check_command(command1[0], potential_path);
	binary2 = check_command(command2[0], potential_path);
	// if (command1 == NULL || command2 == NULL)
	// 	exit(EXIT_FAILURE);
	// if (pipe(end) == -1)
	// 	exit(EXIT_FAILURE);
	// id1 = fork();
	// if (id1 == -1)
	// 	exit(EXIT_FAILURE);
	// if (id1)
	// 	id2 = fork();
	// if (id2 == -1)
	// 	exit(EXIT_FAILURE);
	// if (id1 != 0 && id2 != 0)
	// 	while (wait(NULL) != -1)
	// 		;
	// if (!id1)
	// {
	// 	if (!id2)
	// 		execve(command1[0], command1, env);
	// 	else
	// 		execve(command2[0], command2, env);
	// }
	return (0);
}
/*
TODO
check_command(char *path);
valid_file(char *path);
*/
