#include <glad/glad.h>
#include "src/core/core.h"
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

		glClear(GL_COLOR_BUFFER_BIT);

		system.ventana.swapBuffers(system.ventanon);

    }

    system.cleanupSystem();

    return 0;
}