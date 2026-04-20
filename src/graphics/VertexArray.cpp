#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
}

void VertexArray::LinkVBO(VertexBuffer VertexBuffer, GLuint layout, GLuint size, GLuint stride, GLuint offset)
{
	VertexBuffer.Bind();
	glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(layout);
}

void VertexArray::Bind()
{
	glBindVertexArray(ID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::Delete()
{
	glDeleteVertexArrays(1, &ID);
}