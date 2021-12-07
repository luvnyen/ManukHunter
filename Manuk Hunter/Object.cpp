#include "Object.h"

//const
Object::Object(sf::Sprite sprite, sf::Texture texture)
{
	this->sprite = sprite;
	this->texture = texture;
}
Object::~Object()
{

}

//PAM
void Object::setTexture(std::string file)
{
	//load a texture from file
	this->texture.loadFromFile(file);
}
void Object::setSprite(float x, float y)
{
	//set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//resize the sprite
	this->sprite.scale(x, y);
}
const sf::Vector2f& Object::getPos() const
{
	return this->sprite.getPosition();
}
sf::FloatRect Object::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
std::string Object::getType()
{
	return "Object";
}
void Object::setSmoothTexture()
{
	this->texture.setSmooth(true);
}
