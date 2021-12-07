#pragma once

#include "Enemy.h"

class RegularEnemy : public Enemy
{
private:
	//private functions
	void initTexture();
	void initSprite();
	void initVariables();

public:
	//const
	RegularEnemy(sf::Sprite sprite = sf::Sprite(), sf::Texture texture = sf::Texture(), float movement_speed = 0, int health = 0);
	~RegularEnemy();

	//PAM
	std::string getType();
};