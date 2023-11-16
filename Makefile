# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 18:46:57 by dgarizad          #+#    #+#              #
#    Updated: 2023/11/16 16:18:20 by dgarizad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /***
#  *    ________/\\\\\\\\\__/\\\________/\\\__/\\\\\\\\\\\\\____/\\\\\\\\\\\\\\\_________________________/\\\\\\\\\\_________________/\\\\\\\\\\\\____        
#  *     _____/\\\////////__\/\\\_______\/\\\_\/\\\/////////\\\_\/\\\///////////________________________/\\\///////\\\_______________\/\\\////////\\\__       
#  *      ___/\\\/___________\/\\\_______\/\\\_\/\\\_______\/\\\_\/\\\__________________________________\///______/\\\________________\/\\\______\//\\\_      
#  *       __/\\\_____________\/\\\_______\/\\\_\/\\\\\\\\\\\\\\__\/\\\\\\\\\\\_________________________________/\\\//____/\\\\\\\\\\\_\/\\\_______\/\\\_     
#  *        _\/\\\_____________\/\\\_______\/\\\_\/\\\/////////\\\_\/\\\///////_________________________________\////\\\__\///////////__\/\\\_______\/\\\_    
#  *         _\//\\\____________\/\\\_______\/\\\_\/\\\_______\/\\\_\/\\\___________________________________________\//\\\_______________\/\\\_______\/\\\_   
#  *          __\///\\\__________\//\\\______/\\\__\/\\\_______\/\\\_\/\\\__________________________________/\\\______/\\\________________\/\\\_______/\\\__  
#  *           ____\////\\\\\\\\\__\///\\\\\\\\\/___\/\\\\\\\\\\\\\/__\/\\\\\\\\\\\\\\\_____________________\///\\\\\\\\\/_________________\/\\\\\\\\\\\\/___ 
#  *            _______\/////////_____\/////////_____\/////////////____\///////////////________________________\/////////___________________\////////////_____
#  */

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
NAMEBONUS := cub3d_bonus
LIBMLX := ./lib/MLX42
LIBFT = ./libft/libft.a
HEADERS := "-I./inc -I$(LIBMLX)/include"
HEADER = cub3d.h
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
LIBS	:= -ldl -lglfw -L "/Users/dgarizad/.brew/opt/glfw/lib/" -lm $(LIBMLX)/libmlx42.a
OBJDIR = ./obj
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRC = cub3d.c game.c mapanal.c mapanal2.c mapcheck.c mapcheck2.c mini_sprites.c \
movements.c parsing_elements.c parsing_elements_2.c parsing_elements_3.c \
rayban.c textureparsing.c utils.c utils2.c

SRCBONUS = cub3d.c game_bonus.c mapanal.c mapanal2.c mapcheck.c mapcheck2_bonus.c mini_sprites.c \
movements.c parsing_elements.c parsing_elements_2.c parsing_elements_3.c \
rayban.c textureparsing.c utils.c utils2.c

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

OBJSBONUS = $(addprefix $(OBJDIR)/, $(SRCBONUS:.c=.o))

$(OBJDIR)/%.o: %.c $(HEADER)
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

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

$(NAMEBONUS): $(OBJSBONUS) $(LIBFT)
	@echo "$(GREEN)Compilation ${CLR_RMV}of BONU! ${YELLOW}$(NAMEBONUS) ${CLR_RMV}..."
	@$(CC) $(OBJSBONUS) $(LIBFT) $(LIBS) -o $(NAMEBONUS)
	@echo "Done."

$(LIBFT): 
	@echo "Your beloved ${YELLOW}libft${CLR_RMV}..."
	@make -C ./libft

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME) $(NAMEBONUS)
	@$(MAKE) -C $(LIBMLX) fclean
	@$(MAKE) -C ./libft fclean

re: clean all

bonus: libmlx $(NAMEBONUS)

.PHONY: all, clean, fclean, re, libmlx, bonus