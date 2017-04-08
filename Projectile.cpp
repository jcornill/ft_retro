#include "Projectile.hpp"
#include "Game.hpp"
#include "Display.hpp"
#include "Logger.hpp"

Projectile::Projectile(void) {

}

Projectile::Projectile(Projectile const & src) {
	*this = src;
}

Projectile::Projectile(int posX, int posY, char drawingChar, int speed, bool dir, bool ally, int damage ) :
Entity(posX, posY, drawingChar), _dir(dir), _ally(ally), _damage(damage)
{
	this->_speed = speed;
}

Projectile::~Projectile(void) {

}

Projectile &	Projectile::operator=(Projectile const & rhs) {
	if (this != &rhs){

	}
	return (*this);
}

int Projectile::GetDamage() const
{
	return this->_damage;
}

void Projectile::Colision(Entity *entity)
{
	if (_ally)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(entity);
		if (enemy)
		{
			enemy->TakeDamage(this->_damage);
			Game::Instance->RemoveEntity(this);
		}
	}
}

void Projectile::Update()
{
	this->_frameCount++;
	if (this->_frameCount >= this->_speed)
	{
		this->_frameCount = 0;
		this->_oldX = this->_posX;
		this->_posX++;
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
