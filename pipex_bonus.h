/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:17:39 by ymassiou          #+#    #+#             */
/*   Updated: 2024/02/28 17:27:04 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

typedef struct s_process
{
	char	*path;
	char	**command;
	int		pid;
	int		fd;
}		t_process;

char	**ft_split(char const *s, char c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *s1);
char	*create_path(char **paths, char *command);
char	*check_command(char *command, char **paths);
char	*get_env(char **env);
char	*extract_path(char **env);
int		valid_file(char *path, int in_or_out);
void	*ft_free(char **to_free, size_t elements);
void	child1_do(char *path, int *p_fds, char **command1, char **env);
void	child2_do(char *path, int *p_fds, char **command2, char **env);
void	errno_protocol(void);
size_t	ft_strcmp(char *s1, char *s2);
char	*get_next_line(int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
#endif
