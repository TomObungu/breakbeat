#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.hpp"
#include "Shader.hpp"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};

// A renderer class for rendering text displayed by a font loaded using the 
// FreeType library. A single font is loaded, processed into a list of Character
// items for later rendering.
class TextRenderer
{
public:
    // holds a list of pre-compiled Characters
    std::map<char, Character> mCharacters; 
    // shader used for text rendering
    
    Shader mShader;
    // constructor
    TextRenderer(unsigned int width, unsigned int height);
    // pre-compiles a list of characters from the given font
    void Load(string font, unsigned int fontSize);
    // renders a string of text using the precompiled list of characters
    void RenderText(string text, float x, float y, float scale, vec3 color = vec3(1.0f));
private:
    // render state
    unsigned int mVetexArrayObject, mVertexBufferObject;
};

#endif 