#ifndef LIVING_ENTITY_HPP
# define LIVING_ENTITY_HPP
# include "Entity.hpp"

class LivingEntity : public Entity {
	public:
		LivingEntity(LivingEntity const & src);
		virtual ~LivingEntity(void);
		LivingEntity & operator=(LivingEntity const & rhs);

		void	Shoot();
		virtual void	TakeDamage(int damage);
		int		GetHp() const;
		int		GetMaxHp() const;
		int		GetDamage() const;
		virtual void 	Heal(int amount);

	protected:
		LivingEntity(void);
		LivingEntity(int posX, int posY, char drawingChar, int speed, bool ally, int hp, int damage);
		int _hp;
		int _maxHp;
		int _damage;
};

#endif
