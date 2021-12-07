#pragma once

#include "Enemy.h"

class FastEnemy : public Enemy
{
private:
	//private functions
	void initTexture();
	void initSprite();
	void initVariables();

public:
	//const
	FastEnemy(sf::Sprite sprite = sf::Sprite(), sf::Texture texture = sf::Texture(), float movement_speed = 0, int health = 0);
	~FastEnemy();

	//PAM
	std::string getType();
};