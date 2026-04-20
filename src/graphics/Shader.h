#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>


class Shader
{
public:
    GLuint ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use();
	void Delete();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private:
    void checkCompileErrors(unsigned int shader, std::string type);
    std::string get_file_contents(const char* filename);
};
