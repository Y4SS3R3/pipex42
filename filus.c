#include "pipex_bonus.h"

void        here_doc_put_in(char **av, int *p_fd)
{
        char        *ret;

        close(p_fd[0]);
        while (1)
        {
                ret = get_next_line(0);
                if (ft_strncmp(ret, av[2], ft_strlen(av[2])) == 0)
                {
                        free(ret);
                        exit(0);
                }
                ft_putstr_fd(ret, p_fd[1]);
                free(ret);
        }
}

void        here_doc(char **av)
{
        int                p_fd[2];
        pid_t        pid;

        if (pipe(p_fd) == -1)
                exit(0);
        pid = fork();
        if (pid == -1)
                exit(0);
        if (!pid)
                here_doc_put_in(av, p_fd);
        else
        {
                close(p_fd[1]);
                dup2(p_fd[0], 0);
                wait(NULL);
        }
}
