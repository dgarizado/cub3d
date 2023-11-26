# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcereced <vcereced@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 18:46:57 by dgarizad          #+#    #+#              #
#    Updated: 2023/11/26 18:05:15 by vcereced         ###   ########.fr        #
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
HEADER = cub3d_bonus.h
CC = gcc -g
CFLAGS = #-Wall -Wextra -Werror
LIBS	:= -ldl -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -lm $(LIBMLX)/libmlx42.a
OBJDIR = ./obj
OBJDIRBONUS = ./obj_bonus
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRC = cub3d.c game.c mapanal.c mapanal2.c mapcheck.c mapcheck2.c mini_sprites.c \
movement.c parsing_elements.c parsing_elements_2.c parsing_elements_3.c \
textureparsing.c utils.c utils2.c  game_aux.c draw_map_intro.c draw_texture.c draw_steven.c\
draw_title_intro.c draw_title_intro_2.c intro.c utils_2.c utils3.c mini_map.c raycasting_minimap.c casting.c casting_2.c raycasting.c

SRCBONUS = cub3d_bonus.c  mapanal_bonus.c mapanal2_bonus.c mapcheck_bonus.c mapcheck2_bonus.c \
movement_bonus.c movement_3_bonus.c parsing_elements_bonus.c parsing_elements_2_bonus.c \
parsing_elements_3_bonus.c utils_bonus.c utils2_bonus.c utils3_bonus.c draw_title_intro_bonus.c \
draw_title_intro_2_bonus.c loops_bonus.c mini_map_bonus.c raycasting_minimap_bonus.c \
casting_bonus.c casting_2_bonus.c raycasting_bonus.c draw_steven_bonus.c draw_texture_bonus.c \
draw_map_intro_bonus.c parsing_tittle_bonus.c movement_2_bonus.c utils4_bonus.c kill_bonus.c draw_texture_2_bonus.c 

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

OBJSBONUS = $(addprefix $(OBJDIRBONUS)/, $(SRCBONUS:.c=.o))

$(OBJDIR)/%.o: %.c $(HEADER)
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJDIRBONUS)/%.o: %.c $(HEADER)
	@mkdir -p $(OBJDIRBONUS)
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

$(USER):
	USER = whoami

$(LIBFT): 
	@echo "Your beloved ${YELLOW}libft${CLR_RMV}..."
	@make -C ./libft

clean:
	@rm -rf $(OBJDIR) $(OBJDIRBONUS)

fclean: clean
	@rm -f $(NAME) $(NAMEBONUS)
	@$(MAKE) -C $(LIBMLX) fclean
	@$(MAKE) -C ./libft fclean

re: clean all

bonus: libmlx $(NAMEBONUS)

.PHONY: all, clean, fclean, re, libmlx, bonus