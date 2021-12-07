#pragma once

#include "MovingObject.h"

class Item : virtual public MovingObject
{
private:
	//attributes
	float moveTimer;
	float moveTimerMax;
	bool counter;

public:
	//const
	Item(sf::Sprite sprite = sf::Sprite(), sf::Texture texture = sf::Texture(), float movement_speed = 0, float movetimer = 0, float movetimermax = 0, bool counter = false);
	~Item();

	//PAM
	std::string getType();
	void setMoveTimerMax(float movetimermax);
	void setMoveTimer(float movetimer);
	float getMoveTimerMax();
	float getMoveTimer();
	void setCounter(bool counter);
	bool getCounter();
};

