#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

std::string get_file_contents(const char *filename);

class Shader {
public:
    // Reference ID of the Shader Program
    GLuint ID;

    // Constructor that build the Shader Program from 2 different shaders
    Shader(const char *vertexFile, const char *fragmentFile);

    // Activates the Shader Program
    void Activate() const;

    // Deletes the Shader Program
    void Delete() const;

    void setVec2(const std::string &name, glm::vec2 value) const;

    void setVec3(const std::string &name, glm::vec3 value) const;

    void setVec4(const std::string &name, glm::vec4 value) const;


    void setMat4(const std::string &name, glm::mat4 value) const;

    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) const;
};

#endif