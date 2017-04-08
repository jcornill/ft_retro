#ifndef PLAYER_HPP
# define PLAYER_HPP
# include "LivingEntity.hpp"
# include <iostream>

class Player : public LivingEntity
{

public:
    Player(void);
    Player(Player const &src);
    ~Player(void);
    Player &operator=(Player const &rhs);

	void Colision(Entity *entity);
	// Update process player movement
	void Update();
	void Shoot();

private:
	int _attackSpeed;
};

#endif
