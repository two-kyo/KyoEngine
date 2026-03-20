#include "core.h"
#include "game_config.h"

void SystemClass::initSystem() {

	ventana.initialize(windowTitle, windowWidth, windowHeight, ventanon);
}

void SystemClass::cleanupSystem() {
	ventana.cleanup(ventanon);
	SDL_Quit();
}