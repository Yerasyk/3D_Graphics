#pragma once

#include <glad/glad.h>
#include "VertexBuffer.h"

class VertexArray
{
public:
	GLuint ID;
	VertexArray();

	void LinkVBO(VertexBuffer VertexBuffer, GLuint layout, GLuint size, GLuint stride, GLuint offset);
	void Bind();
	void Unbind();
	void Delete();
};

