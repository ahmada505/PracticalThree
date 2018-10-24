#include "pch.h"
#include "InputHandler.h"

InputHandler::InputHandler()
{
	m_currentAction = IDLE;

}

InputHandler::~InputHandler()
{

}
Action InputHandler::getCurrentAction()
{
	return m_currentAction;
}
void InputHandler::setCurrentAction(Action a)
{
	m_currentAction = a;
}

void InputHandler::handleInput(SDL_Event & event, SDL_Rect &destRect)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_1:
			if (getCurrentAction() == IDLE)
			{
				destRect.y = 45;
				destRect.x = 0;
				fsm.climbing();
				setCurrentAction(CLIMBING);
			}
			break;
		case SDLK_2:
			if (getCurrentAction() == IDLE)
			{
				destRect.y = 100;
				destRect.x = 0;
				fsm.jumping();
				setCurrentAction(JUMPING);
			}
			break;
		case SDLK_3:
			destRect.y = 0;
			fsm.idle();
			setCurrentAction(IDLE);
			break;
		}

	}

}