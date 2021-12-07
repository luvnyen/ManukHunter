#pragma once

#include "Item.h"

class FireSpeedDownItem : public Item
{
private:
	//private functions
	void initTexture();
	void initSprite();

public:
	//const
	FireSpeedDownItem(sf::Sprite sprite = sf::Sprite(), sf::Texture texture = sf::Texture(), float movement_speed = 0);
	~FireSpeedDownItem();

	//PAM
	std::string getType();

	//functions
	void setSpawnPoint(sf::RenderTarget& target, float x, float y);
};

