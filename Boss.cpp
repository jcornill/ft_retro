#include "Boss.hpp"
#include "Projectile.hpp"

Boss::Boss(int posX, int posY, char drawingChar, int speed, int hp, int damage, int attackSpeed) :
	Enemy(posX, posY, drawingChar, speed, false, hp, damage, attackSpeed, 0), _up(false), _fire(false), _die(false)
{

}

Boss::Boss(void) {
    return;
}

Boss::Boss(Boss const &src) {
    *this = src;
    return;
}

Boss::~Boss(void) {
    Game::Instance->BossDeath();
}

Boss &Boss::operator=(Boss const &rhs) {
    if (this != &rhs) {

    }
    return *this;
}

void Boss::TakeDamage(int damage)
{
	this->_hp -= damage;
	if (this->_hp <= 0 && !this->_die)
	{
		Game::Instance->AddScore(this->_maxHp);
		this->_damage += 1000;
		this->_die = true;
	}
}

void Boss::Shoot()
{
	if (this->_frameCount % this->_attackSpeed == 0 && this->_fire)
	{
		Projectile *proj = new Projectile(this->_posX - 19, this->_posY + 2, '-', 2, false, false, this->_damage, 0);
		Game::Instance->AddEntity(proj);
		proj = new Projectile(this->_posX - 19, this->_posY + 3, '-', 2, false, false, this->_damage, 0);
		Game::Instance->AddEntity(proj);
		proj = new Projectile(this->_posX - 19, this->_posY + 4, '-', 2, false, false, this->_damage, 0);
		Game::Instance->AddEntity(proj);
	}
	if (this->_frameCount % this->_attackSpeed == 0)
	{
		if (this->_hp <= this->_maxHp / 2)
		{
			Projectile *proj = new Projectile(this->_posX - 19, this->_posY + 3, '/', 5, false, false, this->_damage, 1);
			Game::Instance->AddEntity(proj);
			proj = new Projectile(this->_posX - 19, this->_posY + 3, '\\', 5, false, false, this->_damage, -1);
			Game::Instance->AddEntity(proj);
		}
		if (this->_hp <= this->_maxHp / 4)
		{
			Projectile *proj = new Projectile(this->_posX - 15, this->_posY + 5, '/', 5, false, false, this->_damage, 1);
			Game::Instance->AddEntity(proj);
			proj = new Projectile(this->_posX - 15, this->_posY, '\\', 5, false, false, this->_damage, -1);
			Game::Instance->AddEntity(proj);
		}
		if (this->_hp <= this->_maxHp / 4 && this->_fire)
		{
			Projectile *proj = new Projectile(this->_posX - 19, this->_posY + 1, '-', 2, false, false, this->_damage, 0);
			Game::Instance->AddEntity(proj);
			proj = new Projectile(this->_posX - 19, this->_posY + 5, '-', 2, false, false, this->_damage, 0);
			Game::Instance->AddEntity(proj);
		}
		if (this->_hp <= this->_maxHp / 8 && this->_fire)
		{
			Projectile *proj = new Projectile(this->_posX - 19, this->_posY, '-', 2, false, false, this->_damage, 0);
			Game::Instance->AddEntity(proj);
			proj = new Projectile(this->_posX - 19, this->_posY + 6, '-', 2, false, false, this->_damage, 0);
			Game::Instance->AddEntity(proj);
		}
	}
}

void Boss::Update()
{
	if (this->_die)
	{
		this->_oldX = this->_posX;
		this->_posX--;
	}
	else
	{
		this->_frameCount++;
		this->Shoot();
		if (this->_frameCount % 75 == 0)
			this->_fire = true;
		if (this->_frameCount % 300 == 0)
			this->_fire = false;
		if (this->_frameCount % this->_speed == 0)
		{
			this->_oldX = this->_posX;
			this->_oldY = this->_posY;
			if (this->_up)
			{
				if (this->_posY > 1)
				{
					this->_posY--;
				}
				else
				{
					this->_up = false;
				}
			}
			else
			{
				if (this->_posY < Display::sizeY - 8)
				{
					this->_posY++;
				}
				else
				{
					this->_up = true;
				}
			}
		}
	}
	if (Display::IsInMap(this->_posX, this->_posY))
	{
		Display::Erase(this->_oldX, this->_oldY);
		Display::PutChar(_drawingChar, this->_posX, this->_posY);
		Entity::Update();
	}
	else
	{
		Display::Erase(this->_oldX, this->_oldY);
		Game::Instance->RemoveEntity(this);
	}
}
