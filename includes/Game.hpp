#ifndef GAME_HPP
# define GAME_HPP
# define NB_ENTITY 1000
# include "Entity.hpp"
# include "Enemy.hpp"
# include "Player.hpp"
# include <ctime>

class Game {
	public:
		Game(void);
		Game(Game const & src);
		virtual ~Game(void);
		Game & operator=(Game const & rhs);

		// The Game loop
		void	GameLoop();
		void	AddEntity(Entity *entity);
		void	RemoveEntity(Entity *entity);
		void	Spawn();
		void	ProcessCollision();
		void	QueryInput();
		bool	IsKeyPressed(int key);
		int 	GetScore() const;
		void	RemoveAllEntities();

		void	AddScore(int score);
		void	StopGame();
		Player *GetPlayer();
		void	SpawnBoss();
		void	BossDeath();

		static Game *Instance;

	private:
		void	ParseString(Entity *entity, std::string charArray, int paddingStart);
		int _score;
		// Array de pointeur sur entity
		Entity *entityList[NB_ENTITY];
		bool	keys[256];
		clock_t _start;
		clock_t _end;
		bool _stop;
		int _gameFrame;
		int _difficulty;
		bool _pause;
		bool _boss;
};

#endif
