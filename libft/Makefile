# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anammal <anammal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 13:08:18 by anammal           #+#    #+#              #
#    Updated: 2022/10/09 13:08:18 by anammal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC =	$(shell ls ft_*.c | grep -v "bonus.c")
BSRC =	$(shell ls ft_*_bonus.c)
GNL = get_next_line.c
CFLAGS += -Wall -Wextra -Werror
OBJS = $(SRC:.c=.o)
BOBJS = $(BSRC:.c=.o)
BGNL = $(GNL:.c=.o)
R=\033[1;31m
G=\033[1;32m
Y=\033[1;33m
NC=\033[1;0m


all: $(NAME)
	@echo "$(G)The compilation of $(NAME) was successful.$(NC)"

$(NAME): $(OBJS)
	@ar rcs $@ $(OBJS)

bonus: $(BOBJS)
	@echo "$(G)The compilation of $(NAME) (bonus) was successful.$(NC)"
	@ar rcs $(NAME) $(BOBJS)

gnl: $(BGNL)
	@echo "$(G)The compilation of $(NAME) (gnl) was successful.$(NC)"
	@ar rcs $(NAME) $(BGNL)

%.o: %.c $(NAME:.a=.h)
	@echo "$(Y) Compiling: $< ... Done$(NC)!"
	@cc $(CFLAGS) -c $<

clean:
	@echo "$(R)The object file has been cleaned.$(NC)"
	@rm -f $(OBJS)
	@rm -f $(BOBJS)
	@rm -f $(BGNL)

fclean: clean
	@echo "$(R)The libft library has been completely cleaned.$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
