# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 18:46:57 by dgarizad          #+#    #+#              #
#    Updated: 2023/10/20 21:13:13 by dgarizad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -rf

NAME := cub3d
LIBMLX := ./lib/MLX42
LIBFT = ./libft/libft.a
HEADERS := "-I./inc -I$(LIBMLX)/include"
HEADER = ./inc/so_long.h
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
LIBS	:= -ldl -lglfw -L "/Users/dgarizad/.brew/opt/glfw/lib/" -lm $(LIBMLX)/libmlx42.a

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################


SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
%.o: %.c $(HEADER)
	@echo "Creating objects..."
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) 

################################################################################
#                                  Makefile  objs                              #
################################################################################

all: libmlx $(NAME)

libmlx:
	@echo "Compiling MLX42..."
	@$(MAKE) -C $(LIBMLX)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
	@$(CC) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "Done."

$(LIBFT): 
	@echo "Your beloved ${YELLOW}libft${CLR_RMV}..."
	@make -C ./libft
clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBMLX) fclean
	@$(MAKE) -C ./libft fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx