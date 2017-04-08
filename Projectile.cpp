#include "Projectile.hpp"

Projectile::Projectile(void) {

}

Projectile::Projectile(Projectile const & src) {
	*this = src;
}

Projectile::Projectile(int damage, bool right) {

}

Projectile::~Projectile(void) {

}

Projectile &	Projectile::operator=(Projectile const & rhs) {
	if (this != &rhs){

	}
	return (*this);
}
