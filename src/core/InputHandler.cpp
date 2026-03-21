#include "InputHandler.h"

Input::Input() {}

void Input::bindAction(std::string action, SDL_Scancode key)
{
	actionKeyMap[action] = key;
	currentKeyState[key] = false;
	previousKeyState[key] = false;
}

void Input::update()
{
	for (const auto& pair : actionKeyMap) {
		SDL_Scancode key = pair.second;
		previousKeyState[key] = currentKeyState[key];
		currentKeyState[key] = SDL_GetKeyboardState(NULL)[key];
	}
}

bool Input::isActionPressed(const char* action)
{
	SDL_Scancode key = actionKeyMap[action];
	return currentKeyState[key];
}

bool Input::isActionTriggered(const char* action)
{
	SDL_Scancode key = actionKeyMap[action];
	return currentKeyState[key] && !previousKeyState[key];
}

bool Input::isActionReleased(const char* action)
{
	SDL_Scancode key = actionKeyMap[action];
	return !currentKeyState[key] && previousKeyState[key];
}