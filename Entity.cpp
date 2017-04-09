#include "Entity.hpp"
#include "Display.hpp"
#include "Logger.hpp"

Entity::Entity(void) : _posX(1), _posY(1), _oldX(1), _oldY(1), _hasPosChanged(false), _drawingChar('>')
{
	Display::PutChar(_drawingChar, this->_posX, this->_posY);
}

Entity::Entity(int posX, int posY, char drawingChar, int speed, bool ally) :
_posX(posX), _posY(posY), _oldX(posX), _oldY(_posY), _hasPosChanged(false),
_drawingChar(drawingChar), _speed(speed), _frameCount(0), _isCollide(true),
_ally(ally)
{
	Display::PutChar(_drawingChar, this->_posX, this->_posY);
}

Entity::Entity(Entity const & src) {
	*this = src;
}

Entity::~Entity(void) {

}

Entity &	Entity::operator=(Entity const & rhs) {
	if (this != &rhs){
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
	}
	return (*this);
}


int Entity::GetPosX() const
{
	return this->_posX;
}

int Entity::GetPosY() const
{
	return this->_posY;
}

bool Entity::GetCollide() const
{
	return this->_isCollide;
}

bool Entity::GetAlly() const
{
	return this->_ally;
}
