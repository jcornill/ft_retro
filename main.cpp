#include <ncurses.h>
#include "Display.hpp"
#include "Game.hpp"
#include "Logger.hpp"

int main() {
	Display *nCurse = new Display(210, 42);
	if (nCurse->IsInit())
	{
		bool relaunch = true;
		while (relaunch) {
			Game::Instance->GameLoop();
			delete Game::Instance;
			Game::Instance = 0;
			delete nCurse;

			nCurse = new Display(210, 42);
			Display::PutStr("G A M E   O V E R ", (Display::sizeX / 2) - 7, Display::sizeY / 2);
			Display::PutStr("Press r to relaunch", (Display::sizeX / 2) - 7, (Display::sizeY / 2) + 2);
			Display::PutStr("Press q to quit", (Display::sizeX / 2) - 7, (Display::sizeY / 2) + 3);

			Display::Refresh();
			bool isRunning = true;
			while (isRunning) {
				int key = Display::GetKey();
				if (key == 'q') {
					isRunning = false;
					relaunch = false;
				}
				if (key == 'r') {
					isRunning = false;
					Game::Instance = new Game();
					delete nCurse;
					nCurse = new Display(210, 42);
				}
			}
		}
	}
	else
	{
		Logger::LogToFile("Error when loading ncurses !");
	}
	//delete Game::Instance;
	delete nCurse;
}
