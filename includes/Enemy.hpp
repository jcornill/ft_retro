#ifndef ENEMY_HPP
# define ENEMY_HPP
# include "LivingEntity.hpp"

class Enemy : public LivingEntity {
	public:
		Enemy(void);
		Enemy(Enemy const & src);
		~Enemy(void);
		Enemy & operator=(Enemy const & rhs);
};

#endif
