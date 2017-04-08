#include "LivingEntity.hpp"
#include "Game.hpp"
#include "Display.hpp"

LivingEntity::LivingEntity(void) : Entity(), _hp(100), _maxHp(100), _damage(5) {

}

LivingEntity::LivingEntity(int posX, int posY, char drawingChar, int speed, bool ally, int hp, int damage) :
	Entity(posX, posY, drawingChar, speed, ally), _hp(hp), _maxHp(hp), _damage(damage) {

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
		Game::Instance->AddScore(this->_maxHp);
		Display::Erase(this->_posX, this->_posY);
		Game::Instance->RemoveEntity(this);
	}
}

int LivingEntity::GetHp() const
{
	return this->_hp;
}

int LivingEntity::GetMaxHp() const
{
	return this->_maxHp;
}

int LivingEntity::GetDamage() const
{
	return this->_damage;
}
