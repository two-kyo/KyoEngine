#ifndef _WINDOWHANDLER_H
#define _WINDOWHANDLER_H

#include <SDL3/SDL.h>

class windowHandler {
private:
	SDL_GLContext glContext;
public:

	int initialize(const char* title, int width, int height, SDL_Window*& window);
	void swapBuffers(SDL_Window*);
	void cleanup(SDL_Window*& window);
};

#endif