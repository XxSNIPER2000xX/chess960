// cpp libs
#include <iostream>

// c libs
#include <cstdlib>

// third party libs
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// defines & consts

const unsigned int SCR_HEIGHT   = 480;
const unsigned int SCR_WIDTH    = 640;

int main(int argc, char **argv) {
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

    while(!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return EXIT_SUCCESS;
}
