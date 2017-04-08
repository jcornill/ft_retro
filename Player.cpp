#include "Player.hpp"
#include "Display.hpp"
#include "Logger.hpp"
#include "Projectile.hpp"
#include "Game.hpp"

Player::Player(void) {
    return;
}

Player::Player(Player const &src) {
    *this = src;
    return;
}

Player::~Player(void) {
    return;
}

Player &Player::operator=(Player const &rhs) {
    if (this != &rhs) {

    }
    return *this;
}

void Player::Shoot()
{
	Projectile *proj = new Projectile(this->_posX + 1, this->_posY, '-', 3, true, true, this->_damage);
	Game::Instance->AddEntity(proj);
}

void Player::Update()
{
	int i = Display::GetKey();
	if (i != -1)
	{
		this->_oldX = this->_posX;
		this->_oldY = this->_posY;
		switch (i)
		{
		case (int)'d':
			this->_posX++;
			this->_hasPosChanged = true;
			break;
		case (int)'a':
			this->_posX--;
			this->_hasPosChanged = true;
			break;
		case (int)'w':
			this->_posY--;
			this->_hasPosChanged = true;
			break;
		case (int)'s':
			this->_posY++;
			this->_hasPosChanged = true;
			break;
		case 32:
			this->Shoot();
			break;
		}
		if (_hasPosChanged)
		{
			if (Display::IsInMap(this->_posX, this->_posY))
			{
				Display::Erase(this->_oldX, this->_oldY);
				Display::PutChar(_drawingChar, this->_posX, this->_posY);
			}
			else
			{
				this->_posX = this->_oldX;
				this->_posY = this->_oldY;
			}
			_hasPosChanged = false;
		}
	}
}
