#pragma once

#include "Item.h"

class FireSpeedUpItem : public Item
{
private:
	//private functions
	void initTexture();
	void initSprite();

public:
	//const
	FireSpeedUpItem(sf::Sprite sprite = sf::Sprite(), sf::Texture texture = sf::Texture(), float movement_speed = 0);
	~FireSpeedUpItem();

	//PAM
	std::string getType();
};

