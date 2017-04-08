#ifndef GAME_HPP
# define GAME_HPP
# include "Entity.hpp"
# include <ctime>

class Game {
	public:
		Game(void);
		Game(Game const & src);
		~Game(void);
		Game & operator=(Game const & rhs);

		// The Game loop
		void GameLoop();

	private:
		int _score;
		// Array de pointeur sur entity
		Entity *entityList[100];
		clock_t _start;
		clock_t _end;
};

#endif
