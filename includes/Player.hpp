#ifndef PLAYER_HPP
# define PLAYER_HPP
# include "LivingEntity.hpp"
# include <iostream>

class Player : public LivingEntity
{

public:
	Player(int posX, int posY, char drawingChar, int hp, int damage, int attackSpeed, bool mainPlayer);
    Player(Player const &src);
    ~Player(void);
    Player &operator=(Player const &rhs);

	void Colision(Entity *entity);
	// Update process player movement
	void Update();
	void Shoot();

private:
	Player(void);
	int _attackSpeed;
	bool _mainPlayer;
};

#endif
