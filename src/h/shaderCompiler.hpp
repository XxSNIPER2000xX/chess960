#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include <GL/glew.h>

uint32_t createShaderProgram();
uint32_t compileShader(const std::string &shaderPath, GLenum type);
std::string loadShaderAsString(const std::string &fileName);
