#ifndef RESOURCE_H
#define RESOURCE_H

#include "Texture.h"

#include <string>
#include <map>

class ResourceManager
{
public:

	static Texture LoadTexture(const char* fileName, bool alpha, std::string name);

	static Texture GetTexture(std::string name);

private:

	ResourceManager() {};

	static std::map<std::string, Texture> textures;

	static Texture LoadTextureFromFile(const char* fileName, bool alpha);

};


#endif // !RESOURCE_H



