#ifndef MOVEABLE_ENTITY_HPP
# define MOVEABLE_ENTITY_HPP

/*
 * MOVEABLE ENTITY
 * Class for when we wan't to move a entity with linear movement to
 * left or right
**/

class MoveableEntity {
	public:
		MoveableEntity(void);
		MoveableEntity(MoveableEntity const & src);
		~MoveableEntity(void);
		MoveableEntity & operator=(MoveableEntity const & rhs);


		void update(); //Update pos

	protected:
		bool	_right;
		int		_speed;
};

#endif
