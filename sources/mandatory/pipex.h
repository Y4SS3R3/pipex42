/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:11:56 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/17 03:22:15 by ymassiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

typedef struct s_process
{
	char	**envp;
	char	**command;
	int		pid;
	int		out_fd;
	int		in_fd;
	int		special;
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
size_t	ft_strcmp(char *s1, char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *s1);
char	*create_path(char **paths, char *command);
char	*check_command(char *command, char **paths, int *flag);
char	*get_env(char **env);
char	*extract_path(char **env);
int		valid_file(char *path, int in_or_out);
void	*ft_free(char **to_free, size_t elements, int flag);
int		get_length(char **array);
void	check_env(t_process *data, char **env);
void	check_potential_path(t_process *data);
void	ft_putstr_fd(char *s, int fd);
char	**ft_splitws(char const *s);
void	error_v(char *message, t_process *data);
void	error_iv(char *message, t_process *data);
void	error_iii(char *message, char *to_free1,
			t_process *data, char *to_free2);
void	error_ii(char *message, t_process *data, char *to_free);
void	error_i(t_process *data, char *message);
void	first_child(t_process *data, char *first_command);
int		dup2_more(int old, int new);
void	last_child(t_process *data);
void	finish_it(t_process *data);
void	last_free(t_process *data);
void	pass_command(t_process *data, char *command_av);
void	custom_error1(char *message, t_process *data);
void	custom_error2(char *message, t_process *data);
void	custom_error6(t_process *data, char *message);
#endif
