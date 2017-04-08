#ifndef ENTITY_HPP
# define ENTITY_HPP

class Entity {
	public:
		Entity(void);
		Entity(int posX, int posY, int sizeX, int sizeY, bool hasChanged);
		Entity(Entity const & src);
		virtual ~Entity(void);
		Entity & operator=(Entity const & rhs);

		virtual void Update() = 0; // Called every frame from game

	protected:
		int		_posX;
		int		_posY;
		bool	_hasPosChanged;
		char	_drawingChar;
		bool	_right;
		bool	_speed;
};

#endif
