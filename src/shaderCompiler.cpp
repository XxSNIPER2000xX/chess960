/* this file might have a use after free bug :3 */

#include "h/shaderCompiler.hpp"

std::string loadShaderAsString(const std::string &fileName) {
    std::string str = "";
    std::string line = "";
    std::ifstream shaderFile(fileName);

    if(!shaderFile.is_open()) {
        std::cerr << "failed to open file: " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }
    
    while(std::getline(shaderFile, line)) str += line + '\n';
    
    shaderFile.close();
    
    return str;
}

uint32_t compileShader(const std::string &shaderPath, GLenum type) {
    char infoLog[512];
    uint32_t shader = glCreateShader(type);
    int32_t success = 0;
    
    if(!shader) {
        std::cerr << "Error creating shader!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string shaderCode = loadShaderAsString(shaderPath);
    const char *codeArray[] = {shaderCode.c_str()}; // change to apply to code standards
    glShaderSource(shader, 1, codeArray, nullptr);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "shader compilation failed:\n" << infoLog << std::endl;
        glDeleteShader(shader);
        exit(EXIT_FAILURE);
    }
    
    return shader;
}

uint32_t createShaderProgram() {
    char infoLog[512];
    uint32_t fs, vs, shaderProgram;
    int32_t success = 0;

    fs = compileShader("../src/shaders/fs.fs", GL_FRAGMENT_SHADER);
    vs = compileShader("../src/shaders/vs.vs", GL_VERTEX_SHADER);

    shaderProgram = glCreateProgram();
    if(!shaderProgram) {
        std::cerr << "failed to create shader program!" << std::endl;
        exit(EXIT_FAILURE);
    }

    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "linking shader failed:\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    // uniforms go here later

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "invalid shader program:\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    glDetachShader(shaderProgram, fs);
    glDetachShader(shaderProgram, vs);
    glDeleteShader(fs);
    glDeleteShader(vs);

    return shaderProgram;
}
