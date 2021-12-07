#include "FireSpeedDownItem.h"

//private functions
void FireSpeedDownItem::initTexture()
{
	//load a texture from file
	this->setTexture("Textures/Game/Items/virus.png");
	this->setSmoothTexture();
}
void FireSpeedDownItem::initSprite()
{
	this->setSprite(0.1f, 0.1f);
}

//const
FireSpeedDownItem::FireSpeedDownItem(sf::Sprite sprite, sf::Texture texture, float movement_speed) : Item(sprite, texture, movement_speed)
{
	this->initTexture();
	this->initSprite();
	this->setMovementSpeed(1.f);
}
FireSpeedDownItem::~FireSpeedDownItem()
{
}

//PAM
std::string FireSpeedDownItem::getType()
{
	return "FireSpeedDown";
}
void FireSpeedDownItem::setSpawnPoint(sf::RenderTarget& target, float x, float y)
{
	this->sprite.setPosition(
		static_cast<float>(rand() % static_cast<int>(target.getSize().x - x)),
		y
	);
}
