#include <glad/glad.h>
#include "src/core/core.h"
#include <SDL3/SDL.h>      
#include <SDL3/SDL_main.h>

int main(int argc, char* argv[]) {

	std::cout << "Hello, World!" << std::endl;

    SystemClass system;

    system.initSystem();

    bool done = false;
    float rotationAngleX = 0.0f;
    float rotationAngleY = 0.0f;
	unsigned int playertext = system.rendererer.loadTexture("player.png");
    while (!done) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
        system.input.update();


        if (system.input.isActionPressed("Right")) {
			rotationAngleX += 0.1f;
        }
        if (system.input.isActionPressed("Up")) {
			rotationAngleY -= 0.1f;
        }
        if (system.input.isActionPressed("Left")) {
			rotationAngleX -= 0.1f;
        }
        if (system.input.isActionPressed("Down")) {
			rotationAngleY += 0.1f;
        }

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        system.rendererer.drawRect(playertext,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f);

        system.rendererer.drawCube(
            playertext,
            glm::vec3(0.0f, 0.0f, -3.0f),       // Position
            glm::vec3(rotationAngleY, rotationAngleX * 0.5f, 0.0f), // Rotation
            glm::vec3(1.0f, 1.0f, 1.0f)         // Scale
        );

		system.ventana.swapBuffers(system.ventanon);

    }

    system.cleanupSystem();

    return 0;
}