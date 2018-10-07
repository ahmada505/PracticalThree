#include "pch.h"
#include "Idle.h"


Idle::Idle()
{
}


Idle::~Idle()
{
}

void Idle::jumping(Animation* a)
{
	cout << "Jumping" << endl;
	a->setCurrent(new Idle());
	delete this;
}

void Idle::jumping(Animation* a)
{
	cout << "Climbing" << endl;
	a->setCurrent(new Idle());
	delete this;
}