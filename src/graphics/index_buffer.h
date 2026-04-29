#pragma once

#include <glad/glad.h>

class IndexBuffer
{
public:
	GLuint ID;
	IndexBuffer(GLuint* indices, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Delete();
};

