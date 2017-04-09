#include "EntityChild.hpp"
#include "Display.hpp"
#include "Logger.hpp"
#include "Game.hpp"

Entity::Entity(void)
{

}

Entity::Entity(int posX, int posY, char drawingChar, int speed, bool ally) :
_posX(posX), _posY(posY), _oldX(posX), _oldY(_posY), _hasPosChanged(false),
_drawingChar(drawingChar), _speed(speed), _frameCount(0), _isCollide(true),
_ally(ally)
{
	if (!Display::IsInMap(this->_posX, this->_posY))
	{
		Game::Instance->RemoveEntity(this);
		return;
	}
	Display::PutChar(_drawingChar, this->_posX, this->_posY);
	for (int i = 0; i < NB_CHILD; ++i)
	{
		entitiesChild[i] = 0;
	}
}

Entity::Entity(Entity const & src) {
	*this = src;
}

Entity::~Entity(void) {
	if (Display::IsInMap(this->_posX, this->_posY))
		Display::Erase(this->_posX, this->_posY);
	for (int i = 0; i < NB_CHILD; ++i)
	{
		if (entitiesChild[i])
			Game::Instance->RemoveEntity(entitiesChild[i]);
	}
}

Entity &	Entity::operator=(Entity const & rhs) {
	if (this != &rhs){
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
		for (int i = 0; i < NB_CHILD; i++) {
			this->entitiesChild[i] = rhs.entitiesChild[i];
		}
		this->_nbChild = rhs._nbChild;
	}
	return (*this);
}


void Entity::RemoveChild(Entity *child)
{
	for (int i = 0; i < NB_CHILD; ++i) {
		if (entitiesChild[i] == child) {
			entitiesChild[i] = 0;
		}
	}
}

void Entity::AddChild(Entity *child)
{
	EntityChild* child2 = dynamic_cast<EntityChild*>(child);
	for (int i = 0; i < NB_CHILD; ++i) {
		if (entitiesChild[i] == 0) {
			entitiesChild[i] = child2;
			child2->SetParent(this);
			return ;
		}
	}
}

void Entity::Update()
{
	for (int i = 0; i < NB_CHILD; ++i) {
		EntityChild* child2 = dynamic_cast<EntityChild*>(entitiesChild[i]);
		if (child2) {
			child2->UpdatePos(this->_posX, this->_posY);
		}
	}
}

int Entity::GetPosX() const
{
	return this->_posX;
}

int Entity::GetPosY() const
{
	return this->_posY;
}

bool Entity::GetCollide() const
{
	return this->_isCollide;
}

bool Entity::GetAlly() const
{
	return this->_ally;
}
