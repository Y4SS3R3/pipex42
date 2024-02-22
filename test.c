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
	int fd;
	int i = 0;

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
	if (!binary1 || !binary2)
		exit(EXIT_FAILURE);
	//free(paths); TODO++++++++
	if (pipe(end) == -1)
		exit(EXIT_FAILURE);
	id1 = fork();
	if (id1 == -1)
		exit(EXIT_FAILURE);
	if (id1)
	id2 = fork();
	if (id2 == -1)
		exit(EXIT_FAILURE);
	if (id1 != 0 && id2 != 0)
		while (wait(NULL) != -1)
			;
	if (id1 != 0 && !id2)
	{
		fd = open(av[1], O_RDONLY | O_CREAT, 0666);
		if (fd == -1)
			exit(EXIT_FAILURE);
		dup2(fd, 0);
		close(end[0]);
		dup2(end[1], 1);
		close(end[1]);
		close(fd);
		execve(binary1, command1, env);
		exit(EXIT_FAILURE);
	}
	if (!id1 && !id2)
	{
		fd = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd == -1)
			exit(EXIT_FAILURE);
		dup2(end[0], 0);
		close(end[1]);
		dup2(fd ,1);
		close(end[0]);
		execve(binary2, command2, env);
		exit(EXIT_FAILURE);
	}
	return (0);
}
// dup2(old, new);
