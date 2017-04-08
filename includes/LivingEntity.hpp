#ifndef LIVING_ENTITY_HPP
# define LIVING_ENTITY_HPP
# include "Entity.hpp"

class LivingEntity : public Entity {
	public:
		LivingEntity(LivingEntity const & src);
		virtual ~LivingEntity(void);
		LivingEntity & operator=(LivingEntity const & rhs);

		void	Shoot();
		void	TakeDamage(int damage);

	protected:
		LivingEntity(void);
		LivingEntity(int posX, int posY, char _drawingChar);
		int _hp;
		int _maxHp;
		int _damage;
};

#endif
