#include "Bullet.h"

//const
Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, sf::Vector2f curr_velocity)
{
	this->shape.setTexture(*texture);
	this->setSmoothTexture();
	this->shape.setPosition(pos_x, pos_y);
	this->shape.scale(0.025f, 0.025f);
	this->currentVelocity = curr_velocity;
}
Bullet::~Bullet()
{

}

//PAM
sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

//functions
void Bullet::update()
{
	//movement
	this->shape.move(this->currentVelocity);
}
void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
