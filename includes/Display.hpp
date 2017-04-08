#ifndef DISPLAY_HPP
# define DISPLAY_HPP

# include <iostream>
# include <ncurses.h>

class Display {

public:
    Display(void);
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

	// Refresh display (call at end of each frame)
	static void Refresh();

	static int lastKeyPressed;

private:
	static int defaultPosX;
	static int defaultPosY;
};

#endif
