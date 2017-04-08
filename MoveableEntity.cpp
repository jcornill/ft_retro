#include "MoveableEntity.hpp"

MoveableEntity::MoveableEntity(void) : _right(true), _speed(5) {

}

MoveableEntity::MoveableEntity(MoveableEntity const & src) {
	*this = src;
}

MoveableEntity::~MoveableEntity(void) {

}

MoveableEntity &	MoveableEntity::operator=(MoveableEntity const & rhs) {
	if (this != &rhs){

	}
	return (*this);
}
