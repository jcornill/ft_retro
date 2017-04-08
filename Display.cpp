#include "Display.hpp"
#include "Logger.hpp"
#include "Game.hpp"
#include <signal.h>
#include <stdlib.h>

int Display::lastKeyPressed = -1;

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
	Game::Instance->StopGame();
	Logger::LogToFile("Win resized");
}

Display::Display(void)
{
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
	start_color();
	init_color(COLOR_CYAN, 150, 150, 150);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_color(COLOR_RED, 900, 100, 100);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_color(COLOR_GREEN, 50, 600, 50);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	cbreak();
	mousemask(BUTTON1_PRESSED, NULL);
	keypad(stdscr, TRUE);
	noecho();
	Display::sizeX = pSizeX;
	Display::sizeY = pSizeY;
	int mx, my;
	getmaxyx(stdscr, my, mx);
	if (mx <= pSizeX || my <= (pSizeY + 4))
		this->_init = false;
	else
		this->_init = true;
	signal(SIGWINCH, resizeHandler);
	DrawRect(0, 0, pSizeX, pSizeY+4);
	for (int i = 1; i < pSizeX; ++i)
	{
		Display::PutChar('-', i, pSizeY);
	}
	Display::PutStr("Score : ", 2, pSizeY + 2);
	Display::PutStr("Life : ", 18, pSizeY + 2);
	Display::PutStr("Bomb(SPACE) : ", 35, pSizeY + 2);
	Display::PutStr("Use 'q' to quit", 51, pSizeY + 2);
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
	Display::lastKeyPressed = getch();
	return Display::lastKeyPressed;
}

void Display::PutChar(char c, int x, int y)
{
	mvaddch(y, x, c);
}

void Display::PutStr(std::string str, int x, int y)
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

void Display::UpdateScore()
{
	Display::PutStr(std::to_string(Game::Instance->GetScore()), 11, Display::sizeY + 2);
}

void Display::UpdateLife()
{
	Player * player = Game::Instance->GetPlayer();
	if (player)
		Display::PutStr(player->GetStatus(), 26, Display::sizeY + 2);
}

void Display::UpdateBomb()
{
	Player * player = Game::Instance->GetPlayer();
	if (player)
		Display::PutStr(std::to_string(player->GetBomb()), 49, Display::sizeY + 2);
}
