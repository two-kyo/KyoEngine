#ifndef _CORE_H
#define _CORE_H
#include "windowHandler.h"
#include "renderer.h"
#include "InputHandler.h"
#include <iostream>

class SystemClass {
public:

	void initSystem();
	void cleanupSystem();

	windowHandler ventana;
	SDL_Window* ventanon = nullptr;
	rendererClass rendererer;
	Input input;
};

#endif