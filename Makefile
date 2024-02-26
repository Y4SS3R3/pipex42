# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 14:29:45 by ymassiou          #+#    #+#              #
#    Updated: 2024/02/26 15:47:03 by ymassiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRC = srcs/mandatory/ft_split.c \
		srcs/mandatory/ft_substr.c \
		srcs/mandatory/ft_calloc.c \
		srcs/mandatory/ft_strlen.c \
		srcs/mandatory/ft_memset.c \
		srcs/mandatory/ft_strnstr.c \
		srcs/mandatory/ft_strchr.c \
		srcs/mandatory/ft_strjoin.c \
		srcs/mandatory/ft_memcpy.c \
		srcs/mandatory/ft_strdup.c \
		srcs/mandatory/ft_strlcat.c \
		srcs/mandatory/pipex.c \
		srcs/mandatory/pipex_utils.c \
		srcs/mandatory/child_do.c
OBJS = $(SRC:%.c=%.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
INCS = -I ./includes
HEADER = ./includes/pipex.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -Wall -Wextra -Werror -c $< -o $@ $(INCS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
