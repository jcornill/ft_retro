#include "Star.hpp"
#include "Display.hpp"
#include "Game.hpp"

Star::Star(void) {
    return;
}

Star::Star(int posX, int posY, char drawingChar, int speed)
: Entity(posX, posY, drawingChar)
{
	this->_speed = speed;
	drawStr += "\e[100m";
	drawStr += this->_drawingChar;
	drawStr += "\e[49m";
}

Star::Star(Star const &src) {
    *this = src;
    return;
}

Star::~Star(void) {
    return;
}

void Star::Colision()
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
	if (this->_frameCount % this->_speed == 0)
	{
		this->_posX--;
		if (Display::IsInMap(this->_posX, this->_posY))
		{
			Display::Erase(this->_oldX, this->_oldY);
			Display::PutStr(drawStr, this->_posX, this->_posY);
		}
		else
		{
			Game::Instance->RemoveEntity(this);
		}
	}
}
