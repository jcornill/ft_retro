#include "Display.hpp"
#include "Logger.hpp"

int Display::lastKeyPressed = -1;
int Display::defaultPosX = 0;
int Display::defaultPosY = 25;

Display::Display(void)
{
	Logger::LogToFile("Ncurse is loading");
	initscr();
	clear();
	timeout(1);
	curs_set(0);
	noecho();
	Logger::LogToFile("Ncurse finish loading");
    return;
}

Display::Display(Display const &src) {
    *this = src;
    return;
}

Display::~Display(void) {
	Logger::LogToFile("unloading Ncurse");
	endwin();
    return;
}

Display &Display::operator=(Display const &rhs) {
    if (this != &rhs) {

    }
    return *this;
}

int Display::GetKey()
{
	move(Display::defaultPosY, Display::defaultPosX);
	Display::lastKeyPressed = getch();
	return Display::lastKeyPressed;
}

void Display::PutChar(char c, int x, int y)
{
	mvaddch(y, x, c);
	move(Display::defaultPosY, Display::defaultPosX);
}

void Display::PutStr(std::string str, int x, int y) const
{
	mvprintw(y, x, str.c_str());
}

void Display::Erase(int x, int y)
{
	mvaddch(y, x, ' ');
}
//
// void Display::MoveCursor(int x, int y) const
// {
// 	move(y, x);
// }

void Display::Refresh()
{
//	Logger::LogToFile("Refreshing screen");
	refresh();
}
