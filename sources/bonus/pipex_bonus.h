/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:07:35 by ymassiou          #+#    #+#             */
/*   Updated: 2024/03/13 13:53:23 by ymassiou         ###   ########.fr       */
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
	char	**envp;
	char	**command;
	int		pid;
	int		out_fd;
	int		in_fd;
	int		here_doc_fd;
	int		end[2];
	char	**potential_path;
}		t_process;

char	**ft_splitws(char const *s);
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
char	*check_command(char *command, char **paths, int *flag);
char	*get_env(char **env);
char	*extract_path(char **env);
int		valid_file(char *path, int in_or_out);
void	*ft_free(char **to_free, size_t elements);
int		get_next_line(char **line);
int		get_length(char **array);
size_t	ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
int		dup2_more(int old, int new);
void	last_child(t_process *data, int out_fd);
void	ft_putstr_fd(char *s, int fd);
void	error_ii(char *message, t_process *data, char *to_free);
void	error_iii(char *message, char *to_free1,
			t_process *data, char *to_free2);
void	error_iv(char *message, t_process *data);
void	error_v(char *message, t_process *data);
int		find_limiter(char *limiter, char *line, char *tmp);
void	fill_heredoc(char *limiter, t_process *data, char *name);
char	*randomize_file_name(void);
void	hrdc_arg_error(t_process *data);
void	heredocing_time(int ac, char *limiter, t_process *data);
void	arg_error(void);
void	check_potential_path(t_process *data);
void	check_env(t_process *data, char **env);
void	last_child(t_process *data, int out_fd);
void	pass_command1(t_process *data, char *command_av);
void	pass_command2(t_process *data, char *command_av);
int		dup2_more(int old, int new);
void	last_free(t_process *data);
void	finish_it(t_process *data);

#endif
