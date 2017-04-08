#include "Player.hpp"
#include "Display.hpp"
#include "Logger.hpp"

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

void Player::Update()
{
	int i = Display::GetKey();
	Display::Erase(this->_posX, this->_posY);
	switch (i)
	{
	case (int)'d':
		this->_posX++;
		break;
	case (int)'a':
		this->_posX--;
		break;
	case (int)'w':
		this->_posY--;
		break;
	case (int)'s':
		this->_posY++;
		break;
	}
	this->_hasPosChanged = true;
	if (_hasPosChanged)
	{
		Display::PutChar(_drawingChar, this->_posX, this->_posY);
		_hasPosChanged = false;
	}
}
