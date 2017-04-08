#ifndef PROJECTILE_HPP
# define PROJECTILE_HPP
#include "Entity.hpp"

class Projectile : public Entity {
	public:
		Projectile(int posX, int posY, char drawingChar, int speed, bool dir, bool ally, int damage);
		Projectile(Projectile const & src);
		~Projectile(void);
		Projectile & operator=(Projectile const & rhs);

		void Update();
		void Colision(Entity *entity);
		int GetDamage() const;
	private:
		Projectile(void);
		bool _dir;
		int _damage;
};

#endif
