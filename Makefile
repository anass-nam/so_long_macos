# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anammal <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 02:45:24 by anammal           #+#    #+#              #
#    Updated: 2023/06/11 02:45:28 by anammal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME=so_long
HEADER=src/$(NAME:=.h)
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
CC=cc
CFLAGS= -Werror -Wall -Wextra
LFTDIR=libft
LIBFT=$(LFTDIR:=.a)
LFT= -I$(LFTDIR) -L$(LFTDIR) -lft
LMLX= -lmlx -framework OpenGL -framework AppKit

R=\033[1;31m
G=\033[1;32m
Y=\033[1;33m
NC=\033[1;0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LFT) $(LMLX) -o $@
	@echo "$(G)The compilation of $@ was successful.$(NC)"

$(LIBFT):
	@make -C $(LFTDIR)
	@make bonus -C $(LFTDIR)
	@make gnl -C $(LFTDIR)

%.o: %.c $(HEADER)
	@echo "$(Y) Compiling: $< ... Done$(NC)!"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LFTDIR)
	@echo "$(R)The object file has been cleaned.$(NC)"
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LFTDIR)
	@echo "$(R)$(NAME) has been completely cleaned.$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
