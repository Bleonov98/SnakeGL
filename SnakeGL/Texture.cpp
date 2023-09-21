#include "Texture.h"

Texture::Texture()
	: width(0), height(0), imgFormat(GL_RGB), intFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
	glGenTextures(1, &this->ID);
}

void Texture::LoadTexture(const char* fileName, bool alpha)
{
	if (alpha)
	{
		intFormat = GL_RGBA;
		imgFormat = GL_RGBA;
	}
	// load image
	int Width, Height, nrChannels;
	unsigned char* data = stbi_load(fileName, &Width, &Height, &nrChannels, 0);

	Generate(Width, Height, data);

	stbi_image_free(data);
}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
	this->width = width, this->height = height;

	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->intFormat, width, height, 0, this->imgFormat, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}
