#ifndef PLAYER_HPP
# define PLAYER_HPP
# include "LivingEntity.hpp"
# include <iostream>

class Player : public LivingEntity
{

public:
	Player(int posX, int posY, char drawingChar, bool ally, int hp, int damage, int attackSpeed, bool mainPlayer);
    Player(Player const &src);
    virtual ~Player(void);
    Player &operator=(Player const &rhs);

	void Colision(Entity *entity);
	// Update process player movement
	void Update();
	void Shoot();
	int GetBomb();
	std::string GetStatus() const;
	void TakeDamage(int damage);

private:
	Player(void);
	int _attackSpeed;
	bool _mainPlayer;
	int _bomb;
};

#endif
