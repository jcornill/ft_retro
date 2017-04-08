# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcornill <jcornill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/24 18:32:00 by jcornill          #+#    #+#              #
#    Updated: 2017/04/07 23:32:56 by jcornill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_retro
SRC=main.cpp Display.cpp Entity.cpp Game.cpp MoveableEntity.cpp Player.cpp Logger.cpp
OBJ=$(SRC:.cpp=.o)
FLAG=-Wall -Wextra -Werror
INCLUDE=-I includes

$(NAME): $(OBJ)
	clang++ $(FLAG) -o $(NAME) $(OBJ) -lncurses

m: $(NAME)
	@echo "==========PROG=========="
	@./$(NAME)

save:fclean
	git add --all
	git commit -m "Autosaving piscine"
	git push

all:$(NAME)

nf:
	clang++ -o $(NAME) $(INCLUDE) *.cpp -lncurses

nfm: nf
	rm log.txt
	@echo "==========PROG=========="
	@./$(NAME)
	cat log.txt

clean:
	rm -f $(OBJ)

fclean:clean
	rm -f $(NAME)

re:fclean all

%.o:%.cpp
	clang++ -c $< $(FLAG) $(INCLUDE) -o $@

.PHONY: all clean fclean re save m
