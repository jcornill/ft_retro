#ifndef PROJECTILE_HPP
# define PROJECTILE_HPP
#include "Entity.hpp"

class Projectile : public Entity {
	public:
		Projectile(void);
		Projectile(Projectile const & src);
		Projectile(int damage, bool right);
		~Projectile(void);
		Projectile & operator=(Projectile const & rhs);
};

#endif
