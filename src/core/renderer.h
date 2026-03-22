#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class rendererClass {
private:
	unsigned int shaderProgram;
	unsigned int VBO, VAO;

	void compileShaders();
	void setupSquad();
	

public:
	void init(float width, float height);
	void cleanup();
	unsigned int loadTexture(const char* path);
	void drawRect(unsigned int textureID,float x, float y, float width, float height, float r, float g, float b);
	void drawCube(unsigned int textureID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
};

#endif