#ifndef BOSS_HPP
# define BOSS_HPP
# include "Enemy.hpp"
# include <iostream>

class Boss : public Enemy
{

public:
	Boss(int posX, int posY, char drawingChar, int speed, int hp, int damage, int attackSpeed);
    Boss(Boss const &src);
    virtual ~Boss(void);
    Boss &operator=(Boss const &rhs);

	void Update();
	void TakeDamage(int damage);

private:
	Boss(void);
	void Shoot();
	bool _up;
	bool _fire;
	bool _die;
};

#endif
