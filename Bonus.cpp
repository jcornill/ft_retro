#include "Bonus.hpp"

Bonus::Bonus(void) {

}

Bonus::Bonus(Bonus const & src) {
	*this = src;
}

Bonus::Bonus(int posX, int posY, char drawingChar, int speed) : Entity(posX, posY, drawingChar, speed, true) {

}

Bonus::~Bonus(void) {

}

Bonus &	Bonus::operator=(Bonus const & rhs) {
	if (this != &rhs){

	}
	return (*this);
}

void Bonus::Colision(Entity *entity)
{
	Player* player = dynamic_cast<Player*>(entity);
	if (player)
	{
		player->GetBonus();
		Game::Instance->RemoveEntity(this);
		return;
	}
	EntityChild* child = dynamic_cast<EntityChild*>(entity);
	if (child)
	{
		Player* live = dynamic_cast<Player*>(child->GetParent());
		if (live) {
			player->GetBonus();
			Game::Instance->RemoveEntity(this);
		}
		return;
	}
}

void Bonus::Update()
{
	this->_frameCount++;
	if (this->_frameCount % this->_speed == 0)
	{
		this->_oldX = this->_posX;
		this->_oldY = this->_posY;
		this->_posX--;
		this->_hasPosChanged = true;
		if (_hasPosChanged)
		{
			if (Display::IsInMap(this->_posX, this->_posY))
			{
				Display::Erase(this->_oldX, this->_oldY);
				attron(COLOR_PAIR(3));
				Display::PutChar(_drawingChar, this->_posX, this->_posY);
				attroff(COLOR_PAIR(3));
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
