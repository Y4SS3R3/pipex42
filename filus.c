#include "pipex.h"

int main (int ac, char **av, char **envp)
{
	int fd;
	(void)ac;
	fd = open("infile.txt",O_CREAT | O_TRUNC | O_RDWR, 0777);
	dup2(fd, 0);
	printf(">>>>>>bytes %zd\n",write(0, "massioui ras l9lwa",19));
	close(fd);
	close(0);
	return 0;
}
