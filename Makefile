# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 14:29:45 by ymassiou          #+#    #+#              #
#    Updated: 2024/03/02 16:07:14 by ymassiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
SRC = sources/mandatory/ft_split.c \
		sources/mandatory/ft_substr.c \
		sources/mandatory/ft_calloc.c \
		sources/mandatory/ft_strlen.c \
		sources/mandatory/ft_memset.c \
		sources/mandatory/ft_strnstr.c \
		sources/mandatory/ft_strchr.c \
		sources/mandatory/ft_strjoin.c \
		sources/mandatory/ft_memcpy.c \
		sources/mandatory/ft_strdup.c \
		sources/mandatory/ft_strlcat.c \
		sources/mandatory/pipex.c \
		sources/mandatory/pipex_utils.c \
		sources/mandatory/child_do.c

SRC_BONUS =	sources/bonus/ft_memset_bonus.c \
			sources/bonus/ft_strjoin_bonus.c \
			sources/bonus/ft_strnstr_bonus.c \
			sources/bonus/ft_calloc_bonus.c \
			sources/bonus/ft_split_bonus.c \
			sources/bonus/ft_strlcat_bonus.c \
			sources/bonus/ft_substr_bonus.c \
			sources/bonus/pipex_utils_bonus.c \
			sources/bonus/ft_itoa_bonus.c \
			sources/bonus/ft_strchr_bonus.c \
			sources/bonus/ft_strlen_bonus.c \
			sources/bonus/gnl_bonus.c \
			sources/bonus/ft_memcpy_bonus.c \
			sources/bonus/ft_strdup_bonus.c \
			sources/bonus/ft_strncmp_bonus.c \
			sources/bonus/pipex_bonus.c
OBJS = $(SRC:%.c=%.o)
OBJS_BONUS = $(SRC_BONUS:%.c=%.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
INCS = -I ./includes
HEADER = pipex.h
HEADER_BONUS = pipex_bonus.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -Wall -Wextra -Werror -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

%.o: %.c $(HEADER_BONUS)
	$(CC) -Wall -Wextra -Werror -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
