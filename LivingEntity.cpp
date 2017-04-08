#include "LivingEntity.hpp"

LivingEntity::LivingEntity(void) : Entity(), _hp(100), _maxHp(100), _damage(10) {

}

LivingEntity::LivingEntity(int posX, int posY, int sizeX, int sizeY, bool hasChanged) :
	Entity(posX, posY, sizeX, sizeY, hasChanged) {

}

LivingEntity::LivingEntity(LivingEntity const & src) {
	*this = src;
}

LivingEntity::~LivingEntity(void) {

}

LivingEntity &	LivingEntity::operator=(LivingEntity const & rhs) {
	if (this != &rhs){

	}
	return (*this);
}

int		LivingEntity::GetHp() const {
	return (_hp);
}

void	LivingEntity::SetHp(int value) {
	this->_hp = value;
}

int		LivingEntity::MaxHp() const {
	return (_maxHp);
}

void LivingEntity::SetMaxHp(int value) {
	this->_maxHp = value;
}

int		LivingEntity::GetDamage() const {
	return (_damage);
}

void	LivingEntity::SetDamage(int value) {
	this->_damage = value;
}
