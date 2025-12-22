# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hachahbo                                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/22 16:00:00 by hachahbo          #+#    #+#              #
#    Updated: 2025/12/22 17:00:00 by hachahbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ls

SRCS		= srcs/main.c \
			  srcs/file_list.c \
			  srcs/read_dir.c \
			  srcs/sorting.c \
			  srcs/display.c \
			  srcs/display_long.c \
			  srcs/parse_args.c \
			  srcs/recursive.c \
			  srcs/utils.c

OBJS		= $(SRCS:.c=.o)

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I includes -I Libft_42

LIBFT_DIR	= Libft_42
LIBFT		= $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "✅ ft_ls compiled successfully!"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)
	@echo "🧹 Object files cleaned"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	@echo "🧹 ft_ls cleaned"

re: fclean all

run: all
	./$(NAME)

test: all
	@echo "\n=== Testing ft_ls ===" 
	@echo "\n1. Basic listing:"
	./$(NAME)
	@echo "\n2. With hidden files (-a):"
	./$(NAME) -a
	@echo "\n3. Long format (-l):"
	./$(NAME) -l
	@echo "\n4. Combined flags (-la):"
	./$(NAME) -la

.PHONY: all clean fclean re run test
