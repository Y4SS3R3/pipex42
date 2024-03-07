/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:07:35 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/06 15:33:37 by ymassiou         ###   ########.fr       */
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

#define BUFFER_SIZE 42

typedef struct s_process
{
	char	*path;
	char	**envp;
	char	**command;
	int		pid;
	int		fd;
	int		end[2];
	char	**potential_path;
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
void	errno_protocol(void);
int		get_next_line(char **line);
int		get_lenght(char **array);
size_t	ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
int		dup2_more(int old, int new);
void	pass_command(t_process *data, char *command_av);
void	last_child(t_process *data, int out_fd);
#endif
