#include "Player.hpp"
#include "Display.hpp"
#include "Logger.hpp"
#include "Projectile.hpp"
#include "EntityChild.hpp"
#include "LivingEntity.hpp"
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
	LivingEntity(posX, posY, drawingChar, 0, ally, hp, damage), _attackSpeed(attackSpeed), _mainPlayer(mainPlayer),
	_bomb(3), _bonusLevel(0)
{
		//Display::UpdateLife();
}

Player::~Player(void) {
    return;
}

Player &Player::operator=(Player const &rhs) {
    if (this != &rhs) {
		this->_attackSpeed = rhs._attackSpeed;
		this->_mainPlayer = rhs._mainPlayer;
		this->_bomb = rhs._bomb;
		this->_hp = rhs._hp;
		this->_maxHp = rhs._maxHp;
		this->_damage = rhs._damage;
		this->_posX = rhs._posX;
		this->_posY = rhs._posY;
		this->_oldX = rhs._oldX;
		this->_oldY = rhs._oldY;
		this->_hasPosChanged = rhs._hasPosChanged;
		this->_drawingChar = rhs._drawingChar;
		this->_speed = rhs._speed;
		this->_frameCount = rhs._frameCount;
		this->_isCollide = rhs._isCollide;
		this->_ally = rhs._ally;
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
		Projectile *proj = new Projectile(this->_posX + 15, this->_posY + 2, '-', 2, true, true, this->_damage, 0);
		Game::Instance->AddEntity(proj);
		proj = new Projectile(this->_posX + 15, this->_posY + 3, '-', 2, true, true, this->_damage, 0);
		Game::Instance->AddEntity(proj);
		if (this->_bonusLevel > 0)
		{
			proj = new Projectile(this->_posX + 15, this->_posY + 2, '\\', 5, true, true, this->_damage, 1);
			Game::Instance->AddEntity(proj);
			proj = new Projectile(this->_posX + 15, this->_posY + 3, '/', 5, true, true, this->_damage, -1);
		 	Game::Instance->AddEntity(proj);
		}
		if (this->_bonusLevel > 1)
		{
			proj = new Projectile(this->_posX + 17, this->_posY + 2, '\\', 5, true, true, this->_damage, 1);
			Game::Instance->AddEntity(proj);
			proj = new Projectile(this->_posX + 17, this->_posY + 3, '/', 5, true, true, this->_damage, -1);
			Game::Instance->AddEntity(proj);
		}
		for (int i = 2; i < this->_bonusLevel; ++i)
		{
			proj = new Projectile(this->_posX + 15, this->_posY + 2, '-', 2, true, true, this->_damage, 2);
		 	Game::Instance->AddEntity(proj);
		}
	}
}

void Player::Colision(Entity *entity)
{
	Projectile* proj = dynamic_cast<Projectile*>(entity);
	if (proj)
	{
		if (proj->GetAlly())
			return;
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
		return;
	}
	EntityChild* child = dynamic_cast<EntityChild*>(entity);
	if (child)
	{
		if (child->GetAlly() == this->_ally)
			return;
		LivingEntity* parent = dynamic_cast<LivingEntity*>(child->GetParent());
		int vDamage = parent->GetDamage() * 10;
		Display::Erase(parent->GetPosX(), parent->GetPosY());
		Game::Instance->RemoveEntity(parent);
		this->TakeDamage(vDamage);
		return;
	}
}

bool Player::IsChildOut()
{
	for (int i = 0; i < NB_CHILD; ++i) {
		EntityChild* child2 = dynamic_cast<EntityChild*>(entitiesChild[i]);
		if (child2) {
			if (!child2->UpdatePos(this->_posX, this->_posY))
				return true;
		}
	}
	return false;
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

	if (Display::IsInMap(this->_posX, this->_posY) && !this->IsChildOut())
	{
		Display::Erase(this->_oldX, this->_oldY);
		Display::PutChar(_drawingChar, this->_posX, this->_posY);
	}
	else
	{
		this->_posX = this->_oldX;
		this->_posY = this->_oldY;
		for (int i = 0; i < NB_CHILD; ++i) {
			EntityChild* child2 = dynamic_cast<EntityChild*>(entitiesChild[i]);
			if (child2) {
				child2->UpdatePos(this->_posX, this->_posY);
			}
		}
	}
	if (this->_hasPosChanged)
		this->_hasPosChanged = false;
}

void Player::GetBonus()
{
	this->_bonusLevel++;
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
