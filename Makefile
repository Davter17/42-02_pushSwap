# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: event <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/05 20:39:17 by event             #+#    #+#              #
#    Updated: 2025/04/05 20:39:21 by event            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

SRCS = alg_push.c alg_reverse_rotate.c alg_rotate.c alg_swap.c check_errors.c \
       generate_slot.c main.c slot_utils_advance.c slot_utils_basic.c \
	   turk_algorithm.c update_nodes.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra
CC = cc

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -Ilibft

.PHONY: all clean fclean re libft_clean libft_fclean

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)
	chmod +x $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean: libft_clean
	rm -f $(OBJS)

fclean: clean libft_fclean
	rm -f $(NAME)

re: fclean all

libft_clean:
	$(MAKE) -C $(LIBFT_DIR) clean

libft_fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
