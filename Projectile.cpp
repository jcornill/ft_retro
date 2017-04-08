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

}
