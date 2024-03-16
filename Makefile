# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymassiou <ymassiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 14:29:45 by ymassiou          #+#    #+#              #
#    Updated: 2024/03/16 02:03:44 by ymassiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
SRC = sources/mandatory/ft_split.c \
		sources/mandatory/lib_utils.c \
		sources/mandatory/lib_utils2.c \
		sources/mandatory/lib_utils3.c \
		sources/mandatory/pipex.c \
		sources/mandatory/error_utils.c\
		sources/mandatory/error_utils2.c\
		sources/mandatory/pipex_utils.c \
		sources/mandatory/pipex_utils2.c \
		sources/mandatory/pipex_utils3.c \
		sources/mandatory/ft_splitws.c

SRC_BONUS =	sources/bonus/error_utils_bonus.c \
			sources/bonus/error_utils2_bonus.c \
			sources/bonus/gnl_bonus.c \
			sources/bonus/lib_utils_bonus.c \
			sources/bonus/lib_utils2_bonus.c \
			sources/bonus/pipex_utils_bonus.c \
			sources/bonus/ft_itoa_bonus.c \
			sources/bonus/here_doc_bonus.c \
			sources/bonus/here_doc_utils_bonus.c \
			sources/bonus/paths_bonus.c \
			sources/bonus/pipex_utils2_bonus.c \
			sources/bonus/ft_split_bonus.c \
			sources/bonus/ft_splitws_bonus.c \
			sources/bonus/pipex_bonus.c \
			sources/bonus/pipex_utils3_bonus.c
OBJS_BONUS = $(SRC_BONUS:%.c=%.o)
OBJS = $(SRC:%.c=%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INCS = -I ./includes
HEADER = sources/mandatory/pipex.h
HEADER_BONUS = sources/bonus/pipex_bonus.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

$(OBJS): $(HEADER)

$(OBJS_BONUS): $(HEADER_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
