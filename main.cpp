#include <ncurses.h>
#include "Display.hpp"
#include "Game.hpp"
#include "Logger.hpp"

int main() {
	Display nCurse = Display(210, 42);
	if (nCurse.IsInit())
	{
		Game::Instance->GameLoop();
	}
	else
	{
		Logger::LogToFile("Error when loading ncurses !");
	}
	delete Game::Instance;
}
