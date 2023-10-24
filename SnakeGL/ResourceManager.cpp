#include "ResourceManager.h"

std::map<std::string, Texture> ResourceManager::textures;

Texture ResourceManager::LoadTexture(const char* fileName, bool alpha, std::string name)
{
	std::string filePath = "../textures/";
	filePath += fileName;

	textures[name] = LoadTextureFromFile(filePath.c_str(), alpha);
	return textures[name];
}

Texture ResourceManager::GetTexture(std::string name)
{
	return textures[name];
}

Texture ResourceManager::LoadTextureFromFile(const char* fileName, bool alpha)
{
	Texture txt;

	if (alpha)
	{
		txt.SetAlpha(true);
		txt.SetFormatAlpha();
	}
	// load image
	int Width, Height, nrChannels;
	unsigned char* data = stbi_load(fileName, &Width, &Height, &nrChannels, 0);

	txt.Generate(Width, Height, data);

	stbi_image_free(data);

	return txt;
}

