#include <ncurses.h>
#include "Display.hpp"
#include "Game.hpp"
#include "Logger.hpp"

	Game *gGame;

int main() {
	Display nCurse = Display(210, 42);
	if (nCurse.IsInit())
	{
		Game game = Game();
		gGame = &game;
		game.GameLoop();
	}
	else
	{
		Logger::LogToFile("Error when loading ncurses !");
	}
}
