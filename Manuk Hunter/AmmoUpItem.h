#pragma once

#include "Item.h"

class AmmoUpItem : public Item
{
private:
	//private functions
	void initTexture();
	void initSprite();

public:
	//const
	AmmoUpItem(sf::Sprite sprite = sf::Sprite(), sf::Texture texture = sf::Texture(), float movement_speed = 0);
	~AmmoUpItem();

	//PAM
	std::string getType();
};

