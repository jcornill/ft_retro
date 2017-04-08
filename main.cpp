#include <ncurses.h>
#include "Display.hpp"
#include "Game.hpp"

int main() {
	Display nCurse = Display();
	Game game = Game();
	game.GameLoop();
}
