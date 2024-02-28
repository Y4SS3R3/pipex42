# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 14:29:45 by ymassiou          #+#    #+#              #
#    Updated: 2024/02/27 16:17:37 by ymassiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipexBonus
SRC = ft_split.c \
		ft_substr.c \
		ft_calloc.c \
		ft_strlen.c \
		ft_memset.c \
		ft_strnstr.c \
		ft_strchr.c \
		ft_strjoin.c \
		ft_memcpy.c \
		ft_strdup.c \
		ft_strlcat.c \
		pipex.c \
		pipex_utils.c \
		child_do.c
SRC_BONUS = ft_split.c \
		ft_substr.c \
		ft_calloc.c \
		ft_strlen.c \
		ft_memset.c \
		ft_strnstr.c \
		ft_strchr.c \
		ft_strjoin.c \
		ft_memcpy.c \
		ft_strdup.c \
		ft_strlcat.c \
		pipex_bonus.c \
		pipex_utils.c \
		child_do.c
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

$(NAME): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

%.o: %.c $(HEADER) $(HEADER_BONUS)
	$(CC) -Wall -Wextra -Werror -c $< -o $@

bonus: $(NAME_BONUS)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean:	clean
	$(RM) $(NAME) $(NAME_BONUS)

re:	fclean all

.PHONY:	all clean fclean re
