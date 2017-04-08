#ifndef GAME_HPP
# define GAME_HPP
# define NB_ENTITY 100
# include "Entity.hpp"
# include "Enemy.hpp"
# include <ctime>

class Game {
	public:
		Game(void);
		Game(Game const & src);
		~Game(void);
		Game & operator=(Game const & rhs);

		// The Game loop
		void	GameLoop();
		void	AddEntity(Entity *entity);
		void	RemoveEntity(Entity *entity);
		void	Spawn();

		static Game *Instance;

	private:
		int _score;
		// Array de pointeur sur entity
		Entity *entityList[NB_ENTITY];
		clock_t _start;
		clock_t _end;
};

#endif
