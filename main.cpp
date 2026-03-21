#include <glad/glad.h>
#include "src/core/core.h"
#include <SDL3/SDL.h>      
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]) {

    SystemClass system;

    system.initSystem();

    bool done = false;

    float playerx, playery;     //prototype stuff
	playerx = playery = 0.0f;     //prototype stuff
    Uint64 lastTime = SDL_GetTicks();
    unsigned int playerTexture = system.rendererer.loadTexture("player.png");
    while (!done) {

        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f; 
        lastTime = currentTime;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }

        const bool* keys = SDL_GetKeyboardState(NULL);  //prototype stuff
        float speed = 200.0f * deltaTime;   //prototype stuff

        if (keys[SDL_SCANCODE_UP])    playery -= speed; //prototype stuff
        if (keys[SDL_SCANCODE_DOWN])  playery += speed; //prototype stuff
        if (keys[SDL_SCANCODE_LEFT] and !keys[SDL_SCANCODE_RIGHT])  playerx -= speed;   //prototype stuff
        if (keys[SDL_SCANCODE_RIGHT]) playerx += speed; //prototype stuff


		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        system.rendererer.drawRect(playerTexture,playerx, playery, 96.0f, 97.0f, 1.0f, 1.0f, 1.0f);   //prototype stuff
		system.ventana.swapBuffers(system.ventanon);

    }

    system.cleanupSystem();

    return 0;
}