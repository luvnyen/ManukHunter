#pragma once

#include "MovingObject.h"

class Player : public MovingObject
{
private:
	//attributes
	float attackCooldown;
	float attackCooldownMax;

	//private functions
	void initTexture();
	void initSprite();
	void initVariables();
public:
	//const
	Player(sf::Sprite sprite = sf::Sprite(), sf::Texture texture = sf::Texture(), float movement_speed = 0);
	~Player();

	//PAM
	void setSpawnPoint();
	void setAttackCooldown(float attackcooldown);
	void setAttackCooldownMax(float attackcooldownmax);
	float getAttackCooldown();
	float getAttackCooldownMax();

	//functions
	const bool canAttack();
	void updateAttack();
	void updateWindowCollision(const sf::RenderTarget* target);

	void update(const sf::RenderTarget* target);
};