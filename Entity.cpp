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
		// Don't use getters and setters here
		// direct use this->_pos = rhs._pos
		this->SetPosX(rhs.GetPosX());
		this->SetPosY(rhs.GetPosY());
		this->SetSizeX(rhs.GetSizeX());
		this->SetSizeY(rhs.GetSizeY());
	}
	return (*this);
}

//TODO: Delete getters/setters (cf .hpp)
int		Entity::GetPosX() const {
	return (this->_posX);
}

void	Entity::SetPosX(int value) {
	this->_posX = value;
}

int		Entity::GetPosY() const {
	return (this->_posY);
}

void	Entity::SetPosY(int value) {
	this->_posY = value;
}

int		Entity::GetSizeX() const {
	return (this->_sizeX);
}

void	Entity::SetSizeX(int value) {
	this->_sizeX = value;
}

int		Entity::GetSizeY() const {
	return (this->_sizeY);
}

void	Entity::SetSizeY(int value) {
	this->_sizeY = value;
}
