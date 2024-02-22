#include "pipex.h"

void	get_info(int id1, int id2)
{
	printf("me >>%d\n", getpid());
	printf("my parent >>%d\n", getppid());
	printf("id 1>>%d\nid 2>>%d\n", id1, id2);
	puts("-----------------------");
}

char *check_command(char *command, char **paths)
{
	char *result;
	int i;

	i = 0;
	if (command == NULL)
		return (NULL);
	result = NULL;
	if (ft_strchr(command, '/') == NULL)
	{
		while (paths[i])
		{
			result = ft_strjoin("/", command);
			result = ft_strjoin(paths[i], result);
			if (result == NULL)
				return(NULL);
			if (access(result, X_OK) != -1)
			{
				return (result);
				break;
			}
			free(result);
			i++;
		}
	}
	else
	{
		if (access(command, X_OK) == -1)
		{
			free(command);
			return(NULL);
		}
		else
			result = command;
	}
	return (result);
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
	int i = 0;

	// if (ac < 5)
	// 	exit(EXIT_FAILURE);
	// if (!valid_file(av[1]) || !valid_file(av[4]))
	// 	exit(EXIT_FAILURE);
	command1 = ft_split(av[1], ' ');
	command2 = ft_split(av[2], ' ');
	path = extract_path(env);
	potential_path = ft_split(path, ':');
	binary1 = check_command(command1[0], potential_path);
	binary2 = check_command(command2[0], potential_path);
	if (!binary1 || !binary2)
		exit(EXIT_FAILURE);
	command1[0] = binary1;
	command2[0] = binary2;
	//free(paths); TODO++++++++
	if (pipe(end) == -1)
		exit(EXIT_FAILURE);
	id1 = fork();
	if (id1 == -1)
		exit(EXIT_FAILURE);
	if (!id1)
	{
		puts("hello");
	}
	else
	{
		id2 = fork();
		if (id2 == -1)
			exit(EXIT_FAILURE);
		if (!id2)
			puts("w");
		while (wait(NULL) != -1)
			;
	}
	if (!id2)
		get_info(id1, id2);
	// if (!id1)
	// {
	// 	if (!id2)
	// 	{
	// 		puts("child2");
	// 		execve(binary2, command2, env);
	// 	}
	// 	else
	// 	{
	// 		puts("child1");
	// 		execve(binary1, command1, env);
	// 	}
	// }
	return (0);
}
