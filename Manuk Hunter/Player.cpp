#include "Player.h"

//private functions
void Player::initTexture()
{
	this->setTexture("Textures/Game/Player/player.png");
	this->setSmoothTexture();
}
void Player::initSprite()
{
	this->setSprite(0.35f, 0.35f);
}
void Player::initVariables()
{
	this->setMovementSpeed(3.f);
	this->attackCooldownMax = 30.f;
}

//const
Player::Player(sf::Sprite sprite, sf::Texture texture, float movement_speed) : MovingObject(sprite, texture, movement_speed)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->setSpawnPoint();
}
Player::~Player()
{

}

//PAM
void Player::setSpawnPoint()
{
	this->sprite.setPosition(sf::Vector2f(450.f, 451.f));
}
void Player::setAttackCooldown(float attackcooldown)
{
	this->attackCooldown = attackcooldown;
}
void Player::setAttackCooldownMax(float attackcooldownmax)
{
	this->attackCooldownMax = attackcooldownmax;
}
float Player::getAttackCooldown()
{
	return this->attackCooldown;
}
float Player::getAttackCooldownMax()
{
	return this->attackCooldownMax;
}

//functions
const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}
void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 0.5f;
	}
}
void Player::updateWindowCollision(const sf::RenderTarget* target)
{
	sf::FloatRect playerBounds = this->sprite.getGlobalBounds();
	if (playerBounds.left <= 0.f) {
		this->sprite.setPosition(0, playerBounds.top);
	}
	if (playerBounds.left + playerBounds.width >= target->getSize().x) {
		this->sprite.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
	}
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateAttack();
	this->updateWindowCollision(target);
}