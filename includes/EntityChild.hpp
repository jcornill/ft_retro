#ifndef ENTITY_CHILD_HPP
# define ENTITY_CHILD_HPP
# include <iostream>
# include "Entity.hpp"

class EntityChild : public Entity
{

public:
	EntityChild(Entity *parent, char drawingChar, int rPosX, int rPosY);
	EntityChild(int posX, int posY, char drawingChar, int speed, bool _ally, int rPosX, int rPosY);
    EntityChild(EntityChild const &src);
    virtual ~EntityChild(void);
    EntityChild &operator=(EntityChild const &rhs);

	void Update();
	void Colision(Entity *entity);
	void SetParent(Entity *entity);
	Entity *GetParent();
	bool UpdatePos(int x, int y);

private:
	EntityChild(void);
	int _rPosX;
	int _rPosY;
	Entity *_parent;
};

#endif
