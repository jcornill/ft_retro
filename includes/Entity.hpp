#ifndef ENTITY_HPP
# define ENTITY_HPP

class Entity {
	public:
		Entity(void);
		Entity(int posX, int posY, int sizeX, int sizeY, bool hasChanged);
		Entity(Entity const & src);
		virtual ~Entity(void);
		Entity & operator=(Entity const & rhs);

		// TODO:Delete getters/setters
		// Pas besoin des getter et setter ici
		// On veut pas pouvoir modifie sa taille ou sa position de l'exterieur
		int		GetPosX() const;
		void	SetPosX(int value);
		int		GetPosY() const;
		void	SetPosY(int value);
		int		GetSizeX() const;
		void	SetSizeX(int value);
		int		GetSizeY() const;
		void	SetSizeY(int value);

		virtual void Update() = 0; // Called every frame from game

	protected:
		int _posX;
		int _posY;
		int _sizeX;
		int _sizeY;
		bool _hasPosChanged;
		char _drawingChar;
};

#endif
