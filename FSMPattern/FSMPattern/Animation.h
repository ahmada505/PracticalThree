#pragma once
#include "State.h"
#include "Idle.h"

class Animation
{
	class State* current;
public:
	Animation();
	void setCurrent(State* s) 
	{
		current = s; 
	}
	void idle();
	void jumping();
	void climbing();
};

