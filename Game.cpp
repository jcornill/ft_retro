#include "Game.hpp"
#include "Display.hpp"
#include "Logger.hpp"
#include "Star.hpp"
#include "EntityChild.hpp"
#include <unistd.h>

Game *Game::Instance = new Game();

Game::Game(void) : _score(0), _stop(false), _gameFrame(0)
{
	Logger::LogToFile("Game is loading");

	for (int i = 0; i < NB_ENTITY; ++i)
	{
		entityList[i] = 0;
	}
	for (int i = 0; i < 256; ++i) {
		keys[i] = false;
	}

	Player *player = new Player(6, Display::sizeY / 2, 'H', true, 300, 20, 10, true);
	entityList[0] = player;
	EntityChild *child = new EntityChild(player, '|', -1, 0);
	this->AddEntity(child);
	child = new EntityChild(player, '_', -2, 0);
	this->AddEntity(child);
	child = new EntityChild(player, '[', -3, 0);
	this->AddEntity(child);
	child = new EntityChild(player, '=', -4, 0);
	this->AddEntity(child);
	child = new EntityChild(player, '|', -4, -1);
	this->AddEntity(child);
	child = new EntityChild(player, '_', -4, -2);
	this->AddEntity(child);
	child = new EntityChild(player, '\\', -2, -1);
	this->AddEntity(child);
	child = new EntityChild(player, '=', -4, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '[', -3, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '+', -2, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '-', -1, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '-', 0, 1);
	this->AddEntity(child);
	child = new EntityChild(player, ',', 1, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '-', 2, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '-', 3, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '-', 4, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '-', 5, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '-', 6, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '-', 7, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '-', 8, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '\'', 9, 1);
	this->AddEntity(child);
	child = new EntityChild(player, '_', 9, 0);
	this->AddEntity(child);
	child = new EntityChild(player, '_', 8, 0);
	this->AddEntity(child);
	child = new EntityChild(player, '_', 7, 0);
	this->AddEntity(child);
	child = new EntityChild(player, '_', 6, 0);
	this->AddEntity(child);
	child = new EntityChild(player, '_', 5, 0);
	this->AddEntity(child);
	child = new EntityChild(player, '.', 4, 0);
	this->AddEntity(child);
	child = new EntityChild(player, '-', 3, 0);
	this->AddEntity(child);
	child = new EntityChild(player, '-', 2, 0);
	this->AddEntity(child);
	child = new EntityChild(player, ')', 1, 0);
	this->AddEntity(child);
	child = new EntityChild(player, '[', -3, 2);
	this->AddEntity(child);
	child = new EntityChild(player, '|', -2, 2);
	this->AddEntity(child);
	child = new EntityChild(player, '_', -1, 2);
	this->AddEntity(child);
	child = new EntityChild(player, '/', 0, 2);
	this->AddEntity(child);
	child = new EntityChild(player, '"', 1, 2);
	this->AddEntity(child);
	child = new EntityChild(player, '"', 2, 2);
	this->AddEntity(child);

}

Game::Game(Game const & src) {
	*this = src;
}

Game::~Game(void) {
	Logger::LogToFile("Game is unloading");
	for (int i = 0; i < NB_ENTITY; ++i)
	{
		if (entityList[i]) {
			delete entityList[i];
			entityList[i] = 0;
		}
	}
}

void Game::RemoveAllEntities()
{
	for (int i = 0; i < NB_ENTITY; ++i)
	{
		if (entityList[i]) {
			if (entityList[i]->GetAlly())
				continue;
			Display::Erase(entityList[i]->GetPosX(), entityList[i]->GetPosY());
			delete entityList[i];
			entityList[i] = 0;
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
	Display::UpdateScore();
	Display::UpdateLife();
	Display::UpdateBomb();
	while (1)
	{
		_start = clock();
		// Just here to break game loop when press Q
		if (keys[113]) {
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
		if (this->_stop)
			break;
	}
}

void	Game::RemoveEntity(Entity *entity) {
	for (int i = 0; i < NB_ENTITY; ++i) {
		if (entityList[i] == entity) {
			delete entityList[i];
			entityList[i] = 0;
			if (i == 0)
			{
				this->_stop = true;
			}
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

/*
	  -\
	 <|D
	  -/
*/

void	Game::Spawn() {
	this->_gameFrame++;
	int Difficulty = 0; //(int)((float)this->_gameFrame / 500.0f);
	if (rand() % 42 == 0) {
		int y = (rand() % (Display::sizeY - 1)) + 1;
		Enemy *enemy = new Enemy(Display::sizeX - 1, y, 'D', 5, false, 50 + (Difficulty * 10), 10 + Difficulty, 250 - (Difficulty * 10));
		AddEntity(enemy);
		EntityChild *child = new EntityChild(enemy, '|', -1, 0);
		this->AddEntity(child);
		child = new EntityChild(enemy, '<', -2, 0);
		this->AddEntity(child);
		child = new EntityChild(enemy, '\\', 0, -1);
		this->AddEntity(child);
		child = new EntityChild(enemy, '/', 0, 1);
		this->AddEntity(child);
		child = new EntityChild(enemy, '-', -1, -1);
		this->AddEntity(child);
		child = new EntityChild(enemy, '-', -1, 1);
		this->AddEntity(child);
	}
	if (rand() % 10 == 1) {
		int y = (rand() % (Display::sizeY - 1)) + 1;
		Star *star = new Star(Display::sizeX - 1, y, 'o', 0);
		AddEntity(star);
	}
}

void	Game::ProcessCollision() {
	for (int i = 0; i < NB_ENTITY; ++i) {
		for (int j = i; j < NB_ENTITY; ++j) {
			if (entityList[i] != NULL && entityList[j] != NULL) {
				if (entityList[i]->GetCollide() && entityList[j]->GetCollide() &&
				entityList[i]->GetPosX() == entityList[j]->GetPosX()
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

Player *Game::GetPlayer()
{
	return (Player*)entityList[0];
}

void Game::StopGame()
{
	this->_stop = true;
}
