#ifndef ENTITY_HPP
# define ENTITY_HPP

class Entity {
	public:
		Entity(void);
		Entity(int posX, int posY, char _drawingChar);
		Entity(Entity const & src);
		virtual ~Entity(void);
		Entity & operator=(Entity const & rhs);

		virtual void Update() = 0; // Called every frame from game
		//virtual void Colision(Entity *entity) = 0;

		int GetPosX() const;
		int GetPosY() const;

	protected:
		int		_posX;
		int		_posY;
		int		_oldX;
		int		_oldY;
		bool	_hasPosChanged;
		char	_drawingChar;
		int		_speed;
		int		_frameCount;
};

#endif
