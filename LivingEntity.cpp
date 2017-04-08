#include "LivingEntity.hpp"
#include "Game.hpp"
#include "Display.hpp"

LivingEntity::LivingEntity(void) : Entity(), _hp(100), _maxHp(100), _damage(10) {

}

LivingEntity::LivingEntity(int posX, int posY, char drawingChar) :
	Entity(posX, posY, drawingChar) {

}

LivingEntity::LivingEntity(LivingEntity const & src) {
	*this = src;
}

LivingEntity::~LivingEntity(void) {

}

LivingEntity &	LivingEntity::operator=(LivingEntity const & rhs) {
	if (this != &rhs){
		this->_hp = rhs._hp;
		this->_maxHp = rhs._maxHp;
		this->_damage = rhs._damage;
	}
	return (*this);
}

void LivingEntity::TakeDamage(int damage)
{
	this->_hp -= damage;
	if (this->_hp <= 0)
	{
		Display::Erase(this->_oldX, this->_oldY);
		Game::Instance->RemoveEntity(this);
	}
}
