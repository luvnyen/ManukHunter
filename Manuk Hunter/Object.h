#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Object
{
private:
	//sprite and texture
	sf::Sprite sprite;
	sf::Texture texture;

public:
	//const
	Object(sf::Sprite sprite = sf::Sprite(), sf::Texture texture = sf::Texture());
	~Object();

	//PAM
	void setTexture(std::string file);
	void setSprite(float x, float y);
	const sf::Vector2f& getPos() const;
	sf::FloatRect getBounds() const;
	virtual std::string getType();
	void setSmoothTexture();

	friend class MovingObject;
	friend class Player;
	friend class FireSpeedDownItem;
};

