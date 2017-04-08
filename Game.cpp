#include "Game.hpp"
#include "Player.hpp"
#include "Display.hpp"
#include "Logger.hpp"

#include <unistd.h>

Game *Game::Instance = new Game();

Game::Game(void) : _score(0)
{
	Logger::LogToFile("Game is loading");

	for (int i = 0; i < NB_ENTITY; ++i)
	{
		entityList[i] = 0;
	}
	for (int i = 0; i < 256; ++i) {
		keys[i] = false;
	}

	Player *player = new Player(2, Display::sizeY / 2, '>', 300, 20, 10, true);
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
		if (keys[27]) {
			break ;
		}
		for (int i = 0; i < NB_ENTITY; ++i)
		{
			if (entityList[i])
			{
				entityList[i]->Update(); // Updating all entities
			}
		}
		this->Spawn();
		this->ProcessCollision();
		this->QueryInput();
		Display::Refresh();
		_end = clock();
		unsigned int sleep = (7500 - (_end - _start));
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
	for (int i = 0; i < NB_ENTITY; ++i) {
		if (entityList[i] == 0) {
			entityList[i] = entity;
			return ;
		}
	}
	delete entity;
}

void	Game::Spawn() {
	if (rand() % 42 == 21) {
		int y = (rand() % (Display::sizeY - 1)) + 1;
		Enemy *enemy = new Enemy(Display::sizeX - 1, y, '<', 50, 10, 250);
		AddEntity(enemy);
	}
}

void	Game::ProcessCollision() {
	for (int i = 0; i < NB_ENTITY; ++i) {
		for (int j = i; j < NB_ENTITY; ++j) {
			if (entityList[i] != NULL && entityList[j] != NULL) {
				if (entityList[i]->GetPosX() == entityList[j]->GetPosX()
						&& entityList[i]->GetPosY() == entityList[j]->GetPosY()) {
					entityList[i]->Colision(entityList[j]);
				}
			}
		}
	}
}

void 	Game::QueryInput() {
	for (int i = 0; i < 256; i++ ) {
		this->keys[i] = false;
	}

	int keyPressed[3];
	keyPressed[0] = Display::GetKey();
	//keyPressed[1] = Display::GetKey();
	//keyPressed[2] = Display::GetKey();
	for (int i = 0; i < 1; i++) {
		if (keyPressed[i] != -1) {
			this->keys[keyPressed[i]] = true;
		}
	}
}

bool	Game::IsKeyPressed(int key) {
	if (key >= 0 && key <= 256) {
		return (this->keys[key]);
	}
	return (false);
}

int Game::GetScore() const
{
	return _score;
}

void Game::AddScore(int score)
{
	_score += score;
	Display::UpdateScore();
}
