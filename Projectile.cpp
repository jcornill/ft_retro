#include "Projectile.hpp"

Projectile::Projectile(void) {

}

Projectile::Projectile(Projectile const & src) {
	*this = src;
}

Projectile::Projectile(int posX, int posY, char drawingChar, int speed, bool dir, bool ally, int damage ) :
Entity(posX, posY, drawingChar), _dir(dir), _ally(ally), _damage(damage)
{

}

Projectile::~Projectile(void) {

}

Projectile &	Projectile::operator=(Projectile const & rhs) {
	if (this != &rhs){

	}
	return (*this);
}

void Projectile::Update()
{
	this->_frameCount++;
	if (this->_frameCount == _this->_speed)
	{
		this->_frameCount = 0;
		this->_oldX = this->_posX;
		this->_posX++;
		if (_hasPosChanged)
		{
			if (Display::IsInMap(this->_posX, this->_posY))
			{
				Display::Erase(this->_oldX, this->_oldY);
				Display::PutChar(_drawingChar, this->_posX, this->_posY);
			}
			else
			{
				Game::Instance->RemoveEntity(this);
			}
			_hasPosChanged = false;
		}
	}
}
