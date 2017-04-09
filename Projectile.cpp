#include "Projectile.hpp"
#include "Game.hpp"
#include "Display.hpp"
#include "Logger.hpp"
#include "Player.hpp"
#include "EntityChild.hpp"
#include "LivingEntity.hpp"

Projectile::Projectile(void) {

}

Projectile::Projectile(Projectile const & src) {
	*this = src;
}

Projectile::Projectile(int posX, int posY, char drawingChar, int speed, bool dir, bool ally, int damage , int up) :
Entity(posX, posY, drawingChar, speed, ally), _dir(dir), _damage(damage), _up(up)
{

}

Projectile::~Projectile(void) {

}

Projectile &	Projectile::operator=(Projectile const & rhs) {
	if (this != &rhs){

	}
	return (*this);
}

int Projectile::GetDamage() const
{
	return this->_damage;
}

void Projectile::Colision(Entity *entity)
{
	if (this->_ally)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(entity);
		if (enemy)
		{
			enemy->TakeDamage(this->_damage);
			Display::Erase(this->_posX, this->_posY);
			Game::Instance->RemoveEntity(this);
			return;
		}
	}
	else
	{
		Player* player = dynamic_cast<Player*>(entity);
		if (player)
		{
			player->TakeDamage(this->_damage);
			Display::Erase(this->_posX, this->_posY);
			Game::Instance->RemoveEntity(this);
			return;
		}
	}
	EntityChild* child = dynamic_cast<EntityChild*>(entity);
	if (child)
	{
		if (child->GetAlly() != this->_ally)
		{
			LivingEntity* live = dynamic_cast<LivingEntity*>(child->GetParent());
			live->TakeDamage(this->_damage);
			Display::Erase(this->_posX, this->_posY);
			Game::Instance->RemoveEntity(this);
		}
		return;
	}
}

void Projectile::Update()
{
	this->_frameCount++;
	if (this->_frameCount % this->_speed == 0)
	{
		this->_oldX = this->_posX;
		this->_oldY = this->_posY;
		if (this->_dir)
			this->_posX++;
		else
			this->_posX--;
		if (this->_up == 1)
			this->_posY++;
		else if (this->_up == -1)
			this->_posY--;
		else if (this->_up == 2)
		{
			if (rand() % 2 == 0)
				this->_posY++;
			else
				this->_posY--;
		}

		this->_hasPosChanged = true;
		if (_hasPosChanged)
		{
			if (Display::IsInMap(this->_posX, this->_posY))
			{
				Display::Erase(this->_oldX, this->_oldY);
				if (this->_ally)
					attron(COLOR_PAIR(3));
				else
					attron(COLOR_PAIR(2));
				Display::PutChar(_drawingChar, this->_posX, this->_posY);
				if (this->_ally)
					attroff(COLOR_PAIR(3));
				else
					attroff(COLOR_PAIR(2));
			}
			else
			{
				Display::Erase(this->_oldX, this->_oldY);
				Game::Instance->RemoveEntity(this);
			}
			_hasPosChanged = false;
		}
	}
}
