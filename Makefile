# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdurst <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/14 16:16:42 by rdurst            #+#    #+#              #
#    Updated: 2018/07/05 03:25:35 by rdurst           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
CC=gcc
INCLUDES= -I ./includes -I ./libft/includes/
LIBFT= libft/libft.a
SRCS= ./srcs/main.c\
	./srcs/env.c\
	./srcs/error.c\
	./srcs/exec.c\
	./srcs/exit.c\
	./srcs/signal_handler.c\

OPTIONS= -Wall -Wextra -Werror
DEBUGFLAG= -g3
RM= rm -rf

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m

$(NAME):
	@make -C libft
	@$(CC) $(SRCS) $(INCLUDES) $(LIBFT) -o $(NAME) $(OPTIONS)
	@echo "$(BLUE)\t\t\t\tminishell has been built.$(RESET)"

clean:
	@make -C libft fclean

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BLUE)\t\t\t\tminishell has been removed.$(RESET)"

re: fclean all

all: $(NAME)
