#include <glad/glad.h>
#include "core.h"
#include <SDL3/SDL.h>      
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]) {

    SystemClass system;

    system.initSystem();

    bool done = false;

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }

		glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		system.ventana.swapBuffers(system.ventanon);

    }

    system.cleanupSystem();

    return 0;
}