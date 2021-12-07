#include "FireSpeedUpItem.h"

//private functions
void FireSpeedUpItem::initTexture()
{
	//load a texture from file
	this->setTexture("Textures/Game/Items/thunder.png");
	this->setSmoothTexture();
}
void FireSpeedUpItem::initSprite()
{
	this->setSprite(0.2f, 0.2f);
}

//const
FireSpeedUpItem::FireSpeedUpItem(sf::Sprite sprite, sf::Texture texture, float movement_speed) : Item(sprite, texture, movement_speed)
{
	this->initTexture();
	this->initSprite();
}
FireSpeedUpItem::~FireSpeedUpItem()
{
}

//PAM
std::string FireSpeedUpItem::getType()
{
	return "FireSpeedUp";
}
