#include "Entity.hpp"
#include "Display.hpp"
#include "Logger.hpp"

Entity::Entity(void) : _posX(1), _posY(1), _sizeX(0), _sizeY(0), _hasPosChanged(false), _drawingChar('>') {
	//Logger::LogToFile("Creating Entity");
}

Entity::Entity(int posX, int posY, int sizeX, int sizeY, bool hasChanged) : _posX(posX), _posY(posY),
										_sizeX(sizeX), _sizeY(sizeY), _hasPosChanged(hasChanged){

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
		this->_sizeX = rhs._sizeX;
		this->_sizeY = rhs._sizeY;
	}
	return (*this);
}
