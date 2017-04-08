#include "Game.hpp"
#include "Player.hpp"
#include "Display.hpp"
#include "Logger.hpp"

#include <unistd.h>

Game::Game(void) : _score(0)
{
	Logger::LogToFile("Game is loading");

	for (int i = 0; i < NB_ENTITY; ++i)
	{
		entityList[i] = 0;
	}

	Player *player = new Player();
	entityList[0] = player;
}

Game::Game(Game const & src) {
	*this = src;
}

Game::~Game(void) {
	Logger::LogToFile("Game is unloading");
	for (int i = 0; i < NB_ENTITY; ++i)
	{
		if (entityList[i]) {
			Logger::LogToFile(i);
			delete entityList[i];
		}
	}
}

Game &	Game::operator=(Game const & rhs) {
	if (this != &rhs){

	}
	return (*this);
}

void Game::GameLoop()
{
	Logger::LogToFile("Game loop started");
	srand(time(NULL));
	while (1)
	{
		_start = clock();
		// Just here to break game loop when press ESC
		if (Display::lastKeyPressed == 27)
			break;
		for (int i = 0; i < NB_ENTITY; ++i)
		{
			if (entityList[i])
			{
				entityList[i]->Update(); // Updating all entities
			}
		}
		this->Spawn();
		Display::Refresh();
		_end = clock();
		unsigned int sleep = (5000 - (_end - _start));
		usleep(sleep);
	}
}

void	Game::RemoveEntity(Entity *entity) {
	for (int i = 0; i < NB_ENTITY; ++i) {
		if (entityList[i] == entity) {
			delete entityList[i];
			entityList[i] = 0;
		}
	}
}

void	Game::AddEntity(Entity *entity) {
	Logger::LogToFile("add entity");
	for (int i = 0; i < NB_ENTITY; ++i) {
		if (entityList[i] == 0) {
			entityList[i] = entity;
			break;
		}
	}
}

void	Game::Spawn() {
	if (rand() % 42 == 21) {
		Logger::LogToFile("Enemy spawn");
		int y = rand() % Display::sizeY;
		Enemy *enemy = new Enemy(Display::sizeX - 1, y);
		AddEntity(enemy);
	}
}
