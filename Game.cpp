#include "Game.hpp"
#include "Display.hpp"
#include "Logger.hpp"
#include "Star.hpp"
#include "EntityChild.hpp"
#include "Boss.hpp"
#include <unistd.h>

Game *Game::Instance = new Game();

Game::Game(void) : _score(0), _stop(false), _gameFrame(0), _pause(false), _boss(false)
{
	Logger::LogToFile("Game is loading");

	for (int i = 0; i < NB_ENTITY; ++i)
	{
		entityList[i] = 0;
	}
	for (int i = 0; i < 256; ++i) {
		keys[i] = false;
	}

	Player *player = new Player(7, Display::sizeY / 2, '_', true, 1000, 20, 10, true);
	entityList[0] = player;
	this->ParseString(player, "\n| \\\n=[_|H)--._____\n=[+--,-------'\n [|_/\"\"", 0);
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
			Boss *boss = dynamic_cast<Boss*>(entityList[i]);
			if (boss)
				continue;
			EntityChild *child = dynamic_cast<EntityChild*>(entityList[i]);
			if (child)
			{
				Boss *boss = dynamic_cast<Boss*>(child->GetParent());
				if (boss)
					continue;
			}
			Display::Erase(entityList[i]->GetPosX(), entityList[i]->GetPosY());
			delete entityList[i];
			entityList[i] = 0;
		}
	}
}

Game &	Game::operator=(Game const & rhs) {
	if (this != &rhs){
		this->_score = rhs._score;
		for (int i = 0; i < NB_ENTITY; i++) {
			this->entityList[i] = rhs.entityList[i];
		}
		for (int i = 0; i < 256; i++) {
			this->keys[i] = rhs.keys[i];
		}
		this->_start = rhs._start;
		this->_end = rhs._end;
		this->_stop = rhs._stop;
		this->_gameFrame = rhs._gameFrame;
		this->_difficulty = rhs._difficulty;
		this->_pause = rhs._pause;
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
		this->_gameFrame++;
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
		this->ProcessCollision();
		if (!this->_boss)
			this->Spawn();
		do {
			this->QueryInput();
			if (this->IsKeyPressed('p')) {
				this->_pause = !this->_pause;
			}
		} while (this->_pause);

		if (this->_gameFrame == 10000)
		{
			this->_boss = true;
		}
		if (this->_gameFrame == 11000)
		{
			Logger::LogToFile("Boss Spawn");
			this->SpawnBoss(0);
		}
		if (this->_gameFrame == 30000)
		{
			this->_boss = true;
		}
		if (this->_gameFrame == 31000)
		{
			Logger::LogToFile("Boss Spawn");
			this->SpawnBoss(1);
		}
		Display::Refresh();
		_end = clock();
		int sleep = (7500 - (_end - _start));
		if (sleep > 0)
			usleep(sleep);
		if (this->_stop)
			break;
	}
}

void	Game::SpawnBoss(int id)
{
	if (id == 0)
	{
		Boss *boss = new Boss(Display::sizeX - 25, Display::sizeY / 2, '/', 15, 8000, 10, 10);
		this->AddEntity(boss);
		std::string str;
		str += "~~~~~|\n               .__./''''''|\n";
		str += "._____________/   |/^^^^^^^\\\n|             `===\"\\_______/\n";
		str += "`.             .___/^^^^^^^^\\\n  `------------'~~~\\________/\n";
		str +="                  `........\\\n                   `-------'";
		this->ParseString(boss, str, 20);
	}
	else if (id == 1)
	{
		Boss *boss = new Boss(Display::sizeX - 25, Display::sizeY / 2, '/', 10, 24000, 50, 5);
		this->AddEntity(boss);
		std::string str;
		str += "~~~~~|\n               .__./''''''|\n";
		str += "._____________/   |/^^^^^^^\\\n|             `===\"\\_______/\n";
		str += "`.             .___/^^^^^^^^\\\n  `------------'~~~\\________/\n";
		str +="                  `........\\\n                   `-------'";
		this->ParseString(boss, str, 20);
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

void	Game::Spawn() {
	this->_difficulty = (int)((float)this->_gameFrame / 1000.0f);
	if (rand() % 42 == 0) {
		int enemyType = rand() % 2;
		int y = (rand() % (Display::sizeY - 4)) + 2;
		if (enemyType == 0)
		{
			Enemy *enemy = new Enemy(Display::sizeX - 1, y, '-', 5, false, 50 + (this->_difficulty * 10), 10 + this->_difficulty, 250 - ((this->_difficulty > 20) ? 20 : this->_difficulty * 10), 0);
			this->AddEntity(enemy);
			this->ParseString(enemy, "\\\n<|D\n -/", 1);
		}
		else
		{
			Enemy *enemy = new Enemy(Display::sizeX - 1, y, '\\', 10, false, 25 + (this->_difficulty * 5), 15 + (this->_difficulty * 2), 300 - (this->_difficulty * 5), 1);
			AddEntity(enemy);
			this->ParseString(enemy, "\n|D\n/", 0);
		}
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

void	Game::ParseString(Entity *entity, std::string charArray, int paddingStart) {
	int row = 0;
	int col = 1;
	for (int i = 0; i < (int)charArray.length(); i++) {
		char c = charArray[i];
		if (c == '\n') {
			row++;
			col = -paddingStart;
			continue;
		}
		if (c == ' ') {
			col++;
			continue;
		}
		EntityChild *child = new EntityChild(entity, c, col, row);
		this->AddEntity(child);
		col++;

	}
}

void 	Game::QueryInput() {
	for (int i = 0; i < 256; i++ ) {
		this->keys[i] = false;
	}

	int keyPressed = Display::GetKey();
	if (keyPressed != -1)
		this->keys[keyPressed] = true;
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
	this->_score += (score * (this->_difficulty + 1));
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

void Game::BossDeath()
{
	this->_boss = false;
	if (this->GetPlayer())
		this->GetPlayer()->Heal(1000);
}
