#include "pipex.h"

int main (int ac, char **av, char **envp)
{
	(void)ac;
	if (access(av[1], X_OK) == -1)
		printf("NOPE\n");
	else
		printf("HELL YEAH\n");
	return 0;
}
