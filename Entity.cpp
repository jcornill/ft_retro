#include "Entity.hpp"
#include "Display.hpp"
#include "Logger.hpp"

Entity::Entity(void) : _posX(1), _posY(1), _oldX(1), _oldY(1), _hasPosChanged(false), _drawingChar('>')
{
	Display::PutChar(_drawingChar, this->_posX, this->_posY);
}

Entity::Entity(int posX, int posY, char drawingChar) :
_posX(posX), _posY(posY), _oldX(posX), _oldY(_posY), _hasPosChanged(false), _drawingChar(drawingChar), _frameCount(0)
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
