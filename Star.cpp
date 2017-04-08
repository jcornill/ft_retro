#include "Star.hpp"
#include "Display.hpp"
#include "Game.hpp"

Star::Star(void) {
    return;
}

Star::Star(int posX, int posY, char drawingChar, int speed)
: Entity(posX, posY, drawingChar)
{
	this->_movSpeed = rand() % 3 + 1;
}

Star::Star(Star const &src) {
    *this = src;
    return;
}

Star::~Star(void) {
    return;
}

void Star::Colision(Entity *entity)
{

}

Star &Star::operator=(Star const &rhs) {
    if (this != &rhs) {

    }
    return *this;
}

void Star::Update()
{
	this->_frameCount++;
	if (1)
	{
		this->_oldX = this->_posX;
		this->_oldY = this->_posY;
		this->_posX -= this->_movSpeed;
		if (Display::IsInMap(this->_posX, this->_posY))
		{
			Display::Erase(this->_oldX, this->_oldY);
			attron(COLOR_PAIR(1));
			Display::PutChar(this->_drawingChar, this->_posX, this->_posY);
			attroff(COLOR_PAIR(1));
		}
		else
		{
			Display::Erase(this->_oldX, this->_oldY);
			Game::Instance->RemoveEntity(this);
		}
	}
}
