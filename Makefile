# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 14:23:38 by tforster          #+#    #+#              #
#    Updated: 2024/07/07 14:31:08 by tforster         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED		=	\033[0;31m
GRN		=	\033[0;32m
YLW		=	\033[0;33m
BLU		=	\033[0;34m
MAG		=	\033[0;35m
CYA		=	\033[0;36m
WHT		=	\033[0;37m
RST		=	\033[0m

NAME	=	philo

FILES	=	\
	main.c \
	utils.c \
	init_args.c \
	init_mutex.c \
	init_threads.c \
	routine.c \
	grim_reaper.c \
	logs.c \

SRCDIR	=	src
SRC		=	$(FILES:%.c=$(SRCDIR)/%.o)

OBJDIR	=	obj
OBJ		=	${FILES:%.c=$(OBJDIR)/%.o}

CC		=	cc
CFLGS	=	-pthread -Wextra -Wall -Werror
# CFLGS	=	-g3 -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLGS) $(OBJ) $(INCLUDE) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLGS) $(INCLUDE) -c $< -o $@
	@echo "${GRN}Compile $@ DONE${RST}"

clean:
	@rm -rf $(OBJDIR)
	@echo "${RED}CLEAN:	Objects $(OBJ) DELETED${RST}"

fclean: clean
	@rm -rf $(NAME)
	@echo "${RED}FCLEAN $(NAME) DELETED${RST}"

re: clean all

.PHONY: all, clean, fclean, re


# CVb3d2023
