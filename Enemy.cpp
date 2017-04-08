#include "Enemy.hpp"

Enemy::Enemy(void) {

}

Enemy::Enemy(Enemy const & src) {
	*this = src;
}

Enemy::~Enemy(void) {

}

Enemy &	Enemy::operator=(Enemy const & rhs) {
	if (this != &rhs){

	}
	return (*this);
}
