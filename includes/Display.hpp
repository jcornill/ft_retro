#ifndef DISPLAY_HPP
# define DISPLAY_HPP

# include <iostream>
# include <ncurses.h>

class Display {

public:
    Display(void);
	Display(int pSizeX, int pSizeY);
    Display(Display const &src);
    ~Display(void);
    Display &operator=(Display const &rhs);

	// Return the char press by the player
	static int GetKey();

	// Put a char c at pos x, y
	static void PutChar(char c, int x, int y);

	// Print string str at pos x, y
	void PutStr(std::string str, int x, int y) const;

	// Erase char at pos x, y
	static void Erase(int x, int y);

	// // Move the cursor to the position x, y
	// void MoveCursor(int x, int y) const;

	// Return false if the coord is not in the playable map
	static bool IsInMap(int x, int y);

	// Refresh display (call at end of each frame)
	static void Refresh();

	static int lastKeyPressed;

	bool IsInit();

	static int sizeX;
	static int sizeY;
private:
	static int defaultPosX;
	static int defaultPosY;
	bool _init;
};

#endif
