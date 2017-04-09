#ifndef ENTITY_HPP
# define ENTITY_HPP
# define NB_CHILD 150

class Entity {
	public:
		Entity(int posX, int posY, char drawingChar, int speed, bool _ally);
		Entity(Entity const & src);
		virtual ~Entity(void);
		Entity & operator=(Entity const & rhs);

		virtual void Update(); // Called every frame from game
		virtual void Colision(Entity *entity) = 0;

		int GetPosX() const;
		int GetPosY() const;

		bool GetCollide() const;
		bool GetAlly() const;
		void AddChild(Entity *child);
		void RemoveChild(Entity *child);

	protected:
		Entity(void);
		int			_posX;
		int			_posY;
		int			_oldX;
		int			_oldY;
		bool		_hasPosChanged;
		char		_drawingChar;
		int			_speed;
		int			_frameCount;
		bool		_isCollide;
		bool		_ally;
		Entity		*entitiesChild[NB_CHILD];
		int			_nbChild;
};

#endif
