#include "AmmoUpItem.h"

//private functions
void AmmoUpItem::initTexture()
{
	//load a texture from file
	this->setTexture("Textures/Game/Items/ammo.png");
	this->setSmoothTexture();
}
void AmmoUpItem::initSprite()
{
	this->setSprite(0.2f, 0.2f);
}

//const
AmmoUpItem::AmmoUpItem(sf::Sprite sprite, sf::Texture texture, float movement_speed) : Item(sprite, texture, movement_speed)
{
	this->initTexture();
	this->initSprite();
}
AmmoUpItem::~AmmoUpItem()
{
}

//PAM
std::string AmmoUpItem::getType()
{
	return "AmmoUp";
}
