#include "Enemy.h"

//const
Enemy::Enemy(sf::Sprite sprite, sf::Texture texture, float movement_speed, int health) : MovingObject (sprite, texture, movement_speed) {
	this->health = health;
}
Enemy::~Enemy() {

}

//PAM
void Enemy::setHealth(int health) {
	this->health = health;
}
int Enemy::getHealth() {
	return this->health;
}
std::string Enemy::getType()
{
	return "Enemy";
}