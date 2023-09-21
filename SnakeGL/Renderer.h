#ifndef RENDERER_H
#define RENDERER_H

#include "Texture.h"
#include "Shader.h"

#include <vector>

class Renderer
{
public:

	Renderer() { InitRenderData(); }

	void InitRenderData();
	void AddTexture(const char* fileName, bool alpha);
	void Draw();

	~Renderer();

private:
	
	unsigned int VAO, VBO;
	
	std::vector<Texture> textures;

};

#endif // !RENDERER_H