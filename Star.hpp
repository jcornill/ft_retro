#ifndef STAR_HPP
# define STAR_HPP
# include "Entity.hpp"
# include <iostream>

class Star : public Entity {

public:
    Star(Star const &src);
	Star(int posX, int posY, char drawingChar, int speed);
    ~Star(void);
    Star &operator=(Star const &rhs);

	void Update();
	void Colision();

private:
	Star(void);
	std::string drawStr;

};

#endif
