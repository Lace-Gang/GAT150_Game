#include "Input.h"

#include <SDL.h>

bool Input::Initialize()
{
	int numKeys;
	const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);

	m_keyboardState.resize(numKeys);

	std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());

	m_prevKeyboardState = m_keyboardState;

	return true;
}

void Input::Shutdown()
{
	//
}

void Input::Update()
{
	

	
	//keyboard state
	m_prevKeyboardState = m_keyboardState;

	const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
	std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());


	//mouse state
	int x, y;
	uint32_t buttonState = SDL_GetMouseState(&x, &y);

	m_mousePosition.x = (float)x;
	m_mousePosition.y = (float)y;



	m_prevMouseButtonState = m_mouseButtonState;
	// 000 <- button state
	// 001 <- button mask (what it checks for
	// with the & then 000 would return false, but any combination where the last 0 is a 1 will return true
	m_mouseButtonState[0] = buttonState & SDL_BUTTON_LMASK;
	//checks for 010
	m_mouseButtonState[1] = buttonState & SDL_BUTTON_MMASK;
	//checks for 100
	m_mouseButtonState[2] = buttonState & SDL_BUTTON_RMASK;
}

