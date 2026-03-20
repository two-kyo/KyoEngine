#include "core.h"
#include "../game_config.h"


void SystemClass::initSystem() {

	ventana.initialize(windowTitle, windowWidth, windowHeight, ventanon);
	rendererer.init(640,480);
}

void SystemClass::cleanupSystem() {
	rendererer.cleanup();
	ventana.cleanup(ventanon);
	SDL_Quit();
}