#include "Star.hpp"
#include "Display.hpp"
#include "Game.hpp"

Star::Star(void) {
    return;
}

Star::Star(int posX, int posY, char drawingChar, int speed)
: Entity(posX, posY, drawingChar, speed, true)
{
	this->_movSpeed = rand() % 3 + 1;
	this->_isCollide = false;
}

Star::Star(Star const &src) {
    *this = src;
    return;
}

Star::~Star(void) {
    return;
}

void Star::Colision(Entity *entity)
{
	Game::Instance->RemoveEntity(entity);
}

Star &Star::operator=(Star const &rhs) {
    if (this != &rhs) {
		this->_movSpeed = rhs._movSpeed;
		this->_posX = rhs._posX;
		this->_posY = rhs._posY;
		this->_oldX = rhs._oldX;
		this->_oldY = rhs._oldY;
		this->_hasPosChanged = rhs._hasPosChanged;
		this->_drawingChar = rhs._drawingChar;
		this->_speed = rhs._speed;
		this->_frameCount = rhs._frameCount;
		this->_isCollide = rhs._isCollide;
		this->_ally = rhs._ally;
		for (int i = 0; i < NB_CHILD; i++) {
			this->entitiesChild[i] = rhs.entitiesChild[i];
		}
		this->_nbChild = rhs._nbChild;
    }
    return *this;
}

void Star::Update()
{
	this->_frameCount++;
	this->_oldX = this->_posX;
	this->_oldY = this->_posY;
	this->_posX -= this->_movSpeed;
	if (Display::IsInMap(this->_posX, this->_posY))
	{
		Display::Erase(this->_oldX, this->_oldY);
		attron(COLOR_PAIR(1));
		Display::PutChar(this->_drawingChar, this->_posX, this->_posY);
		attroff(COLOR_PAIR(1));
	}
	else
	{
		Display::Erase(this->_oldX, this->_oldY);
		Game::Instance->RemoveEntity(this);
	}
}
