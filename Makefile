# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcornill <jcornill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/24 18:32:00 by jcornill          #+#    #+#              #
#    Updated: 2017/04/09 16:42:52 by jcornill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_retro
SRC=main.cpp Display.cpp Entity.cpp Game.cpp Player.cpp Logger.cpp Enemy.cpp \
Star.cpp Projectile.cpp LivingEntity.cpp EntityChild.cpp
OBJ=$(SRC:.cpp=.o)
FLAG=-Wall -Wextra -Werror -std=c++98
INCLUDE=-I includes

$(NAME): $(OBJ)
	clang++ $(FLAG) -o $(NAME) $(INCLUDE) $(OBJ) -lncurses

m: $(NAME)
	@echo "==========PROG=========="
	@./$(NAME)

save:fclean
	rm -rf log.txt
	git add --all
	git commit -m "Autosaving rush"
	git push

all:$(NAME)

nf:
	@echo "Prefered to use make m. (We can compile with flag o/)"
	clang++ -o $(NAME) $(INCLUDE) *.cpp -lncurses

nfm: nf
	rm -f log.txt
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
