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
		Enemy(int posX, int posY, char drawingChar, int speed, bool ally, int hp, int damage, int attackSpeed);
		~Enemy(void);
		Enemy & operator=(Enemy const & rhs);

		void Update();
		void Colision(Entity *entity);
		void Shoot();
	private:
		int _attackSpeed;
};

#endif
