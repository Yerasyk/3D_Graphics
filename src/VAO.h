#pragma once

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	GLuint ID;
	VAO();

	void LinkVBO(VBO VBO, GLuint layout, GLuint size, GLuint stride, GLuint offset);
	void Bind();
	void Unbind();
	void Delete();
};

