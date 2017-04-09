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

void LivingEntity::Heal(int amount)
{
	this->_hp += amount;
	if (this->_hp > this->_maxHp)
		this->_hp = this->_maxHp;
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
