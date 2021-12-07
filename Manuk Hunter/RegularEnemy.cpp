#include "RegularEnemy.h"

//private functions
void RegularEnemy::initTexture()
{
	//load a texture from file
	this->setTexture("Textures/Game/Enemies/regular_enemy.png");
	this->setSmoothTexture();
}
void RegularEnemy::initSprite()
{
	this->setSprite(0.1f, 0.1f);
}
void RegularEnemy::initVariables()
{
	this->setMovementSpeed(1.5f);
	this->setHealth(1);
}

//const
RegularEnemy::RegularEnemy(sf::Sprite sprite, sf::Texture texture, float movement_speed, int health) : Enemy(sprite, texture, movement_speed, health)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}
RegularEnemy::~RegularEnemy()
{

}

//PAM
std::string RegularEnemy::getType()
{
	return "Regular";
}
