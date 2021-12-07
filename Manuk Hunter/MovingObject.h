#pragma once

#include "Object.h"

class MovingObject : public Object
{    
private:
	//attributes
	float movementSpeed;

public:
	//const
	MovingObject(sf::Sprite sprite = sf::Sprite(), sf::Texture texture = sf::Texture(), float movement_speed = 0);
	~MovingObject();

	//PAM
	void setMovementSpeed(float movement_speed);
	float getMovementSpeed();

	//functions
	virtual void setSpawnPoint(sf::RenderTarget& target, float x, float y);
	void move(const float dirX, const float dirY);
	void render(sf::RenderTarget& target);
	void update(sf::Vector2f currentvelocity);
};

