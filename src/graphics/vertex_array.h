#pragma once

#include <glad/glad.h>
#include "vertex_buffer.h"

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

