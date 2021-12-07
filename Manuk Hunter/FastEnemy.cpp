#include "FastEnemy.h"

//private functions
void FastEnemy::initTexture()
{
	//load a texture from file
	this->setTexture("Textures/Game/Enemies/fast_enemy.png");
	this->setSmoothTexture();
}
void FastEnemy::initSprite()
{
	this->setSprite(0.3f, 0.3f);
}
void FastEnemy::initVariables()
{
	this->setMovementSpeed(8.f);
	this->setHealth(1);
}

//const
FastEnemy::FastEnemy(sf::Sprite sprite, sf::Texture texture, float movement_speed, int health) : Enemy(sprite, texture, movement_speed, health)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}
FastEnemy::~FastEnemy()
{

}

std::string FastEnemy::getType()
{
	return "Fast";
}