#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "h/shaderCompiler.hpp"

const uint32_t SCR_HEIGHT   = 480;
const uint32_t SCR_WIDTH    = 640;

uint32_t VAO, VBO;

int main() {
    uint32_t shaderProgram;
    GLFWwindow *window;

    if(!glfwInit()) {
        std::cerr << "glfw failed to init!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "chess960", nullptr, nullptr);
    if(!window) {
        std::cerr << "glfw failed to create window!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK) {
        std::cerr << "glew failed to init!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    shaderProgram = createShaderProgram();
    if(!shaderProgram) {
        std::cerr << "shader program failed to init!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    float vertices[] = {
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f,
        0.0f, 0.8f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return EXIT_SUCCESS;
}
