#pragma once
#include <iostream>
#include <glad/glad.h>

class Texture2D
{
public:
	Texture2D(const char* texturePath, GLuint edgeHandling = GL_REPEAT);

	void Bind(GLuint unit);
	void Unbind();
	void Delete();
private:
	GLuint ID = 0;
};

