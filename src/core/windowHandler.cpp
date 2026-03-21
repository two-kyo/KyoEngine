#include <glad/glad.h>
#include "windowHandler.h"

// i apologize 4 whatever the fUCK i made here im so sorry

int windowHandler::initialize(const char* title, int width, int height, SDL_Window*& window) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);

	SDL_SetWindowResizable(window, false);

	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	glContext = SDL_GL_CreateContext(window);
	if (glContext == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create OpenGL context: %s\n", SDL_GetError());
		return 1;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize GLAD");
		return 1;
	}

	glViewport(0, 0, width, height);

	return 0;
}

void windowHandler::swapBuffers(SDL_Window* window) {
	SDL_GL_SwapWindow(window);
}

void windowHandler::cleanup(SDL_Window*& window) {
	SDL_GL_DestroyContext(glContext);
	SDL_DestroyWindow(window);
}