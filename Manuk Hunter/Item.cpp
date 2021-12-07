#include "Item.h"

//const
Item::Item(sf::Sprite sprite, sf::Texture texture, float movement_speed, float movetimer, float movetimermax, bool counter)
{
	this->setMovementSpeed(2.f);
	this->moveTimer = 0;
	this->moveTimerMax = 100.f;
	this->counter = false;
}
Item::~Item()
{

}

//PAM
std::string Item::getType()
{
	return "Item";
}
void Item::setMoveTimerMax(float movetimermax)
{
	this->moveTimerMax = movetimermax;
}
void Item::setMoveTimer(float movetimer)
{
	this->moveTimer = movetimer;
}
float Item::getMoveTimerMax()
{
	return this->moveTimerMax;
}
float Item::getMoveTimer()
{
	return this->moveTimer;
}
void Item::setCounter(bool counter)
{
	this->counter = counter;
}
bool Item::getCounter()
{
	return this->counter;
}