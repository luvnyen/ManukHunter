#pragma once

#include "Enemy.h"

class FatEnemy : public Enemy
{
private:
	//private functions
	void initTexture();
	void initSprite();
	void initVariables();

public:
	//const
	FatEnemy(sf::Sprite sprite = sf::Sprite(), sf::Texture texture = sf::Texture(), float movement_speed = 0, int health = 0);
	~FatEnemy();

	//PAM
	std::string getType();
};