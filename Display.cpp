#include "Display.hpp"
#include "Logger.hpp"
#include <signal.h>
#include <stdlib.h>

int Display::lastKeyPressed = -1;
int Display::defaultPosX = 0;
int Display::defaultPosY = 25;

int Display::sizeX = 210;
int Display::sizeY = 42;

void DrawRect(int px, int py, int sx, int sy)
{
	for (int x = px; x <= sx; ++x)
	{
		for (int y = py; y <= sy; ++y)
		{
			if (y == 0 || y == sy)
				Display::PutChar('*', x, y);
			else if (x == 0 || x == sx)
				Display::PutChar('*', x, y);
		}
	}
}

void resizeHandler(int px)
{
	px = 0;
	Logger::LogToFile("Win resized");
}

Display::Display(void)
{
	Logger::LogToFile("Ncurse is loading");
	initscr();
	clear();
	timeout(1);
	curs_set(0);
	noecho();
	Display::sizeX = 210;
	Display::sizeY = 42;
	DrawRect(0, 0, sizeX, sizeY);
	Logger::LogToFile("Ncurse finish loading");
    return;
}

bool Display::IsInit()
{
	return _init;
}

Display::Display(int pSizeX, int pSizeY)
{
	Logger::LogToFile("Ncurse is loading");
	initscr();
	clear();
	timeout(1);
	curs_set(0);
	noecho();
	Display::sizeX = pSizeX;
	Display::sizeY = pSizeY;
	int mx, my;
	getmaxyx(stdscr, my, mx);
	if (mx < pSizeX || my < pSizeY)
		this->_init = false;
	else
		this->_init = true;
	signal(SIGWINCH, resizeHandler);
	DrawRect(0, 0, pSizeX, pSizeY);
	Logger::LogToFile("Ncurse finish loading");
    return;
}

bool Display::IsInMap(int x, int y)
{
	if (x <= 0 || x >= Display::sizeX)
		return false;
	if (y <= 0 || y >= Display::sizeY)
		return false;
	return true;
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
	//refresh();
}
