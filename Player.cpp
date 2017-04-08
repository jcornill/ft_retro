#include "Player.hpp"
#include "Display.hpp"
#include "Logger.hpp"
#include "Projectile.hpp"
#include "Game.hpp"

Player::Player(void)
{
    return;
}

Player::Player(Player const &src) {
    *this = src;
    return;
}

Player::Player(int posX, int posY, char drawingChar, int hp, int damage, int attackSpeed, bool mainPlayer) :
	LivingEntity(posX, posY, drawingChar, hp, damage), _attackSpeed(attackSpeed), _mainPlayer(mainPlayer) {
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
	if (this->_frameCount % _attackSpeed == 0)
	{
		Projectile *proj = new Projectile(this->_posX + 1, this->_posY, '-', 2, true, true, this->_damage);
		Game::Instance->AddEntity(proj);
	}
}

void Player::Colision(Entity *entity)
{
	Projectile* proj = dynamic_cast<Projectile*>(entity);
	if (proj && !proj->GetAlly())
	{
		int vDamage = proj->GetDamage();
		Display::Erase(proj->GetPosX(), this->GetPosY());
		Game::Instance->RemoveEntity(proj);
		this->TakeDamage(vDamage);
		return;
	}
}

void Player::Update()
{
	this->Shoot();
	this->_frameCount++;
	this->_oldX = this->_posX;
	this->_oldY = this->_posY;
	if (Game::Instance->IsKeyPressed('d')) {
		this->_posX++;
		this->_hasPosChanged = true;
	}
	if (Game::Instance->IsKeyPressed('a')) {
		this->_posX--;
		this->_hasPosChanged = true;
	}
	if (Game::Instance->IsKeyPressed('w')) {
		this->_posY--;
		this->_hasPosChanged = true;
	}
	if (Game::Instance->IsKeyPressed('s')) {
		this->_posY++;
		this->_hasPosChanged = true;
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
