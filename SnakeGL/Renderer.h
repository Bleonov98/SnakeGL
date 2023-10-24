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
	void AddTexture(Texture texture) { this->texture = texture; }
	void Draw();

	~Renderer();

private:
	
	unsigned int VAO, VBO;
	
	Texture texture;

};

#endif // !RENDERER_H