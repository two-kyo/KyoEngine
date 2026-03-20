#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

class rendererClass {
private:
	unsigned int shaderProgram;
	unsigned int VBO, VAO;

	void compileShaders();
	void setupSquad();

public:
	void init(float width, float height);
	void cleanup();

	void drawRect(float x, float y, float width, float height, float r, float g, float b);
};

#endif