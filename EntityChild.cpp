#include "EntityChild.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include "Logger.hpp"

EntityChild::EntityChild(void) {
    return;
}

EntityChild::EntityChild(Entity *parent, char drawingChar, int rPosX, int rPosY)
: Entity(parent->GetPosX(), parent->GetPosY(), drawingChar, 0, parent->GetAlly()), _rPosX(rPosX), _rPosY(rPosY), _parent(parent)
{
	this->_parent->AddChild(this);
}

EntityChild::EntityChild(int posX, int posY, char drawingChar, int speed, bool _ally, int rPosX, int rPosY)
: Entity(posX, posY, drawingChar, speed, _ally), _rPosX(rPosX), _rPosY(rPosY)
{

}

EntityChild::EntityChild(EntityChild const &src) {
    *this = src;
    return;
}

EntityChild::~EntityChild(void) {
    return;
}

void EntityChild::SetParent(Entity *entity)
{
	this->_parent = entity;
}

EntityChild &EntityChild::operator=(EntityChild const &rhs) {
    if (this != &rhs) {

    }
    return *this;
}

void EntityChild::Update()
{
	// if (this->_hasPosChanged)
	// {
		Display::Erase(this->_oldX, this->_oldY);
		Display::PutChar(this->_drawingChar, this->_posX, this->_posY);
		// this->_hasPosChanged = false;
	// }
}

void EntityChild::Colision(Entity *entity)
{
	this->_parent->Colision(entity);
}

Entity *EntityChild::GetParent()
{
	return this->_parent;
}

bool EntityChild::UpdatePos(int x, int y)
{
	x += this->_rPosX;
	y += this->_rPosY;
	if (!Display::IsInMap(x, y))
		return false;
	this->_hasPosChanged = true;
	this->_oldX = this->_posX;
	this->_oldY = this->_posY;
	this->_posX = x;
	this->_posY = y;
	return true;
}
