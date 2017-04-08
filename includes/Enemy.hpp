#ifndef ENEMY_HPP
# define ENEMY_HPP
# include "Game.hpp"
# include "Display.hpp"
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
		void Colision(Entity *entity);
	private:
		bool _dir;
};

#endif
