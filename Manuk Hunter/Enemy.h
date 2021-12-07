#pragma once

#include "MovingObject.h"

class Enemy : virtual public MovingObject
{
private:
	//attributes
	int health;

public:
	//const
	Enemy(sf::Sprite sprite = sf::Sprite(), sf::Texture texture = sf::Texture(), float movement_speed = 0, int health = 0);
	~Enemy();

	//PAM
	void setHealth(int health);
	int getHealth();
	std::string getType();
};