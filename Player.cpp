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

Player::Player(int posX, int posY, char drawingChar, bool ally, int hp, int damage, int attackSpeed, bool mainPlayer) :
	LivingEntity(posX, posY, drawingChar, 0, ally, hp, damage), _attackSpeed(attackSpeed), _mainPlayer(mainPlayer)
	, _bomb(3)
{
		//Display::UpdateLife();
}

Player::~Player(void) {
    return;
}

Player &Player::operator=(Player const &rhs) {
    if (this != &rhs) {

    }
    return *this;
}

void Player::TakeDamage(int damage)
{
	LivingEntity::TakeDamage(damage);
	Display::UpdateLife();
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
		Display::Erase(proj->GetPosX(), proj->GetPosY());
		Game::Instance->RemoveEntity(proj);
		this->TakeDamage(vDamage);
		return;
	}
	Enemy* enemy = dynamic_cast<Enemy*>(entity);
	if (enemy)
	{
		int vDamage = enemy->GetDamage() * 10;
		Display::Erase(enemy->GetPosX(), enemy->GetPosY());
		Game::Instance->RemoveEntity(enemy);
		this->TakeDamage(vDamage);
	}
}

void Player::Update()
{
	this->Shoot();
	this->_frameCount++;
	this->_oldX = this->_posX;
	this->_oldY = this->_posY;
	if (_mainPlayer)
	{
		if (Game::Instance->IsKeyPressed('d')) {
			this->_posX++;
			this->_hasPosChanged = true;
		}
		else if (Game::Instance->IsKeyPressed('a')) {
			this->_posX--;
			this->_hasPosChanged = true;
		}
		else if (Game::Instance->IsKeyPressed('w')) {
			this->_posY--;
			this->_hasPosChanged = true;
		}
		else if (Game::Instance->IsKeyPressed('s')) {
			this->_posY++;
			this->_hasPosChanged = true;
		}
		else if (Game::Instance->IsKeyPressed(32) && this->_bomb > 0)
		{
			this->_bomb--;
			Display::UpdateBomb();
			Game::Instance->RemoveAllEntities();
		}
	}
	// MEVENT event;
	// getmouse(&event);
	// if (event.x != 0 && event.y != 0)
	// {
	// 	this->_posX = event.x;
	// 	this->_posY = event.y;
	// }
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
	if (this->_hasPosChanged)
		this->_hasPosChanged = false;
}

std::string Player::GetStatus() const
{
	std::string result;
	result += std::to_string(this->_hp);
	result += "/";
	result += std::to_string(this->_maxHp);
	return result;
}

int Player::GetBomb()
{
	return this->_bomb;
}
