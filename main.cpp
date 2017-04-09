#include <ncurses.h>
#include "Display.hpp"
#include "Game.hpp"
#include "Logger.hpp"

int main() {
	Display *nCurse = new Display(210, 42);
	if (nCurse->IsInit())
	{
		Game::Instance->GameLoop();
		delete Game::Instance;
		delete nCurse;
//		nCurse = new Display(355, 78);
		Game::Instance = new Game();
		Game::Instance->GameLoop();
	}
	else
	{
		Logger::LogToFile("Error when loading ncurses !");
	}
	delete Game::Instance;
	delete nCurse;
}
