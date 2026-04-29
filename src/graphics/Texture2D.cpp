#include "texture2d.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture2D::Texture2D(const char* texturePath, GLuint edgeHandling)
{
	//Download texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (!data) {
		std::cout << "Failed to load texture" << std::endl;
		return;
	}

	//Support different channel counts (grayscale, RGB, RGBA)
	GLenum format;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;
	else
	{
		std::cout << "Unsupported channel count: " << nrChannels << std::endl;
		stbi_image_free(data);
		return;
	}

	//Generate Texture
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	//Set Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, edgeHandling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, edgeHandling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Load Texture
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

void Texture2D::Bind(GLuint unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Delete() {
	glDeleteTextures(1, &ID);
}