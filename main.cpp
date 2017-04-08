#include <ncurses.h>
#include "Display.hpp"
#include "Game.hpp"

int main() {
	Display nCurse = Display(210, 42);
	Game game = Game();
	game.GameLoop();
}
