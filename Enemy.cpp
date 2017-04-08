#include "Enemy.hpp"
#include "Projectile.hpp"

Enemy::Enemy(void) {

}

Enemy::Enemy(Enemy const & src) {
	*this = src;
}

Enemy::Enemy(int posX, int posY) : LivingEntity(posX, posY, '<') {
	this->_speed = 5;
}

Enemy::~Enemy(void) {

}

Enemy &	Enemy::operator=(Enemy const & rhs) {
	if (this != &rhs){

	}
	return (*this);
}

void Enemy::Colision(Entity *entity)
{
	Projectile* proj = dynamic_cast<Projectile*>(entity);
	if (proj)
	{
		this->TakeDamage(proj->GetDamage());
		Game::Instance->RemoveEntity(this);
	}
}

void Enemy::Update() {
	this->_frameCount++;
	if (this->_frameCount >= this->_speed)
	{
		this->_frameCount = 0;
		this->_oldX = this->_posX;
		this->_posX--;
		this->_hasPosChanged = true;
		if (_hasPosChanged)
		{
			if (Display::IsInMap(this->_posX, this->_posY))
			{
				Display::Erase(this->_oldX, this->_oldY);
				Display::PutChar(_drawingChar, this->_posX, this->_posY);
			}
			else
			{
				Display::Erase(this->_oldX, this->_oldY);
				Game::Instance->RemoveEntity(this);
			}
			_hasPosChanged = false;
		}
	}
}
