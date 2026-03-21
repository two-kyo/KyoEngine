#include "stb_image.h"
#include "renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

//ngl i just copypasted this from a tutorial and i have no idea how it works but it does so who cares

const char* vertexShaderSource = R"glsl(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    layout (location = 1) in vec2 aTexCoord;

    out vec2 TexCoord;
    
    uniform mat4 projection;
    uniform vec2 offset;
    uniform vec2 size;

    void main() {
        
        gl_Position = projection * vec4((aPos * size) + offset, 0.0, 1.0);
        TexCoord = aTexCoord;
    }
)glsl";

const char* fragmentShaderSource = R"glsl(
    #version 330 core
    out vec4 FragColor;
    in vec2 TexCoord;
    uniform sampler2D image;
    
    uniform vec3 rectColor;

    void main() {
        FragColor = texture(image, TexCoord) * vec4(rectColor, 1.0);
    }
)glsl";

void rendererClass::compileShaders() {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void rendererClass::setupSquad() {
    float vertices[] = {
        // Pos X, Y    // Tex U, V
        1.0f, 1.0f,    1.0f, 1.0f, // Bottom Right
        1.0f, 0.0f,    1.0f, 0.0f, // Top Right
        0.0f, 1.0f,    0.0f, 1.0f, // Bottom Left

        1.0f, 0.0f,    1.0f, 0.0f, // Top Right
        0.0f, 0.0f,    0.0f, 0.0f, // Top Left
        0.0f, 1.0f,    0.0f, 1.0f  // Bottom Left
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void rendererClass::init(float width, float height) {
    compileShaders();
    setupSquad();

    glUseProgram(shaderProgram);

    glm::mat4 projection = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);

    int projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void rendererClass::drawRect(unsigned int textureID,float x, float y, float width, float height, float r, float g, float b) {
    glUseProgram(shaderProgram);

    glm::mat4 projection = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);
    int projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    int sizeLoc = glGetUniformLocation(shaderProgram, "size");
    int colorLoc = glGetUniformLocation(shaderProgram, "rectColor");
    int offsetLoc = glGetUniformLocation(shaderProgram, "offset");

    glUniform2f(offsetLoc, x, y);
    glUniform2f(sizeLoc, width, height);
    glUniform3f(colorLoc, r, g, b);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void rendererClass::cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

unsigned int rendererClass::loadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture wrapping/filtering options (good for 2D pixel art)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Use GL_NEAREST for crisp pixel art, GL_LINEAR for smooth HD sprites
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //   nahhh
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;

    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture: " << path << std::endl;
    }

    stbi_image_free(data);
    return textureID;
}