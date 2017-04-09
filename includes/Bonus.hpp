#ifndef BONUS_HPP
# define BONUS_HPP
# include "Entity.hpp"
# include "Game.hpp"
# include "Display.hpp"
# include "Player.hpp"
# include "EntityChild.hpp"

class Bonus : public Entity {
	public:
		Bonus(Bonus const & src);
		Bonus(int posX, int posY, char drawingChar, int speed);
		virtual ~Bonus(void);
		Bonus & operator=(Bonus const & rhs);
		void Update();
		void Colision(Entity *entity);
	private:
		Bonus(void);

};

#endif
