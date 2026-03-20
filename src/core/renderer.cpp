#include "renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

//ngl i just copypasted this from a tutorial and i have no idea how it works but it does so who cares

const char* vertexShaderSource = R"glsl(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    
    uniform mat4 projection;
    uniform vec2 offset;
    uniform vec2 size;

    void main() {
        
        gl_Position = projection * vec4((aPos * size) + offset, 0.0, 1.0);
    }
)glsl";

const char* fragmentShaderSource = R"glsl(
    #version 330 core
    out vec4 FragColor;
    
    uniform vec3 rectColor;

    void main() {
        FragColor = vec4(rectColor, 1.0);
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
        1.0f, 1.0f, // Bottom Right
        1.0f, 0.0f, // Top Right
        0.0f, 1.0f, // Bottom Left
        1.0f, 0.0f, // Top Right
        0.0f, 0.0f, // Top Left
        0.0f, 1.0f  // Bottom Left
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

void rendererClass::drawRect(float x, float y, float width, float height, float r, float g, float b) {

    int offsetLoc = glGetUniformLocation(shaderProgram, "offset");
    int sizeLoc = glGetUniformLocation(shaderProgram, "size");
    int colorLoc = glGetUniformLocation(shaderProgram, "rectColor");

    glUniform2f(offsetLoc, x, y);
    glUniform2f(sizeLoc, width, height);
    glUniform3f(colorLoc, r, g, b);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void rendererClass::cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}