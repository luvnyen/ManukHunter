#include "FatEnemy.h"

//private functions
void FatEnemy::initTexture()
{
	//load a texture from file
	this->setTexture("Textures/Game/Enemies/fat_enemy.png");
	this->setSmoothTexture();
}
void FatEnemy::initSprite()
{
	this->setSprite(0.2f, 0.2f);
}
void FatEnemy::initVariables()
{
	this->setMovementSpeed(1.f);
	this->setHealth(3);
}

//const
FatEnemy::FatEnemy(sf::Sprite sprite, sf::Texture texture, float movement_speed, int health) : Enemy(sprite, texture, movement_speed, health)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}
FatEnemy::~FatEnemy()
{

}

std::string FatEnemy::getType()
{
	return "Fat";
}