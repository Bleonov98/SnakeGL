#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Shader.h"

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};

class TextRenderer
{
public:

    TextRenderer(unsigned int width, unsigned int height);
   
    void Load(std::string font, unsigned int fontSize);

    void RenderText(std::string text, glm::vec2 position, float scale, glm::vec3 color = glm::vec3(1.0f));

private:
   

    std::map<char, Character> Characters;
    Shader txtShader;

    unsigned int VAO, VBO;
};

#endif // TEXT_RENDERER_H