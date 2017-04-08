#ifndef ENEMY_HPP
# define ENEMY_HPP
# include "Entity.hpp"
# include "LivingEntity.hpp"

class Enemy : public LivingEntity {
	public:
		Enemy(void);
		Enemy(Enemy const & src);
		Enemy(int posX, int posY);
		~Enemy(void);
		Enemy & operator=(Enemy const & rhs);

		void Update();
};

#endif
