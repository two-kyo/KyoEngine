#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_
	
#include <SDL3/SDL.h>
#include <map>
#include <string>

class Input {
public:

	Input();

	void bindAction(std::string action, SDL_Scancode key);
	bool isActionPressed(const char* action);
	bool isActionTriggered(const char* action);
	bool isActionReleased(const char* action);
	void update();
private:
	std::map<std::string, SDL_Scancode> actionKeyMap;
	std::map<SDL_Scancode, bool> currentKeyState;
	std::map<SDL_Scancode, bool> previousKeyState;
};

#endif