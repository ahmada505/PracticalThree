#pragma once

#include "Command.h"
#include "Jumping.h"
#include "Climbing.h"
#include "Idle.h"
#include "Animation.h"
#include <SDL.h>

enum Action
{
	IDLE,
	JUMPING,
	CLIMBING
};

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void handleInput(SDL_Event & event, SDL_Rect &destRect);
	Action getCurrentAction();
	void setCurrentAction(Action a);



private:
	Command * buttonX_;
	Command * buttonY_;
	Command * buttonA_;
	Command * buttonB_;
	Command * buttonD_;
	//MacroCommand * macro;
	std::string m_currentState;

	Animation fsm;
	Action m_currentAction;
};