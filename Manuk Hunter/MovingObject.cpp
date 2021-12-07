#include "MovingObject.h"

//const
MovingObject::MovingObject(sf::Sprite sprite, sf::Texture texture, float movement_speed) : Object(sprite, texture)
{
	this->movementSpeed = movement_speed;
}
MovingObject::~MovingObject()
{

}

//PAM
void MovingObject::setMovementSpeed(float movement_speed)
{
	this->movementSpeed = movement_speed;
}
float MovingObject::getMovementSpeed()
{
	return this->movementSpeed;
}

//functions
void MovingObject::setSpawnPoint(sf::RenderTarget& target, float x, float y)
{
	this->sprite.setPosition(
		x,
		static_cast<float>(rand() % static_cast<int>(target.getSize().y - y))
	);
}
void MovingObject::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}
void MovingObject::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
void MovingObject::update(sf::Vector2f currentvelocity)
{
	//movement
	this->sprite.move(currentvelocity);
}
