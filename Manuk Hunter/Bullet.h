#pragma once

#include "MovingObject.h"

class Bullet : public MovingObject
{
private:
	//sprite
	sf::Sprite shape;

	//attributes
	sf::Vector2f currentVelocity;
public:
	//const
	Bullet(sf::Texture* texture, float pos_x = 0, float pos_y = 0, sf::Vector2f curr_velocity = sf::Vector2f());
	~Bullet();

	//PAM
	sf::FloatRect getBounds() const;

	//functions
	void update();
	void render(sf::RenderTarget* target);
};