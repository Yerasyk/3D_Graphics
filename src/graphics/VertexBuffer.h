#pragma once

#include <glad/glad.h>

class VertexBuffer
{
	public:
		GLuint ID;
		VertexBuffer(GLfloat* vertices, GLsizeiptr size);
		void Bind();
		void Unbind();
		void Delete();
};

