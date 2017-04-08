#include "Enemy.hpp"
#include "Projectile.hpp"
#include "Player.hpp"

Enemy::Enemy(void) {

}

Enemy::Enemy(Enemy const & src) {
	*this = src;
}

Enemy::Enemy(int posX, int posY, char drawingChar, int speed, bool ally, int hp, int damage, int attackSpeed) :
LivingEntity(posX, posY, drawingChar, speed, ally, hp, damage), _attackSpeed(attackSpeed)
{

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
	if (proj && proj->GetAlly())
	{
		int vDamage = proj->GetDamage();
		Display::Erase(proj->GetPosX(), this->GetPosY());
		Game::Instance->RemoveEntity(proj);
		this->TakeDamage(vDamage);
		return;
	}
	Player* player = dynamic_cast<Player*>(entity);
	if (player)
	{
		player->TakeDamage(this->_damage * 10);
		Display::Erase(this->_posX, this->_posY);
		Game::Instance->RemoveEntity(this);
		return;
	}
}

void Enemy::Shoot()
{
	if (this->_frameCount % this->_attackSpeed == 0)
	{
		Projectile *proj = new Projectile(this->_posX - 1, this->_posY, '-', 2, false, false, this->_damage);
		Game::Instance->AddEntity(proj);
	}
}

void Enemy::Update() {
	this->_frameCount++;
	this->Shoot();
	if (this->_frameCount % this->_speed == 0)
	{
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
