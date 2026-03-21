#include "core.h"
#include "../game_config.h"


void SystemClass::initSystem() {

	ventana.initialize(windowTitle, windowWidth, windowHeight, ventanon);
	rendererer.init(640,480);
	input.bindAction("Up", SDL_SCANCODE_UP);
	input.bindAction("Down", SDL_SCANCODE_DOWN);
	input.bindAction("Left", SDL_SCANCODE_LEFT);
	input.bindAction("Right", SDL_SCANCODE_RIGHT);
}

void SystemClass::cleanupSystem() {
	rendererer.cleanup();
	ventana.cleanup(ventanon);
	SDL_Quit();
}