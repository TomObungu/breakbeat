#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <map>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Texture.hpp"
#include "Shader.hpp"
#include "GameState.hpp"
#include "Text.hpp"

#include <filesystem>
namespace fs = std::filesystem;

using std::string;
using std::unordered_map;
using std::map;

// A renderer class for rendering text displayed by a font loaded using the 
// FreeType library. A single font is loaded, processed into a list of Character
// items for later rendering.
class TextRenderer
{
public:
unordered_map<string, map<char, Character>> mFonts;
unordered_map<GameState, map<string, Text*>> mCurrentlyRenderedTexts;
unordered_map<GameState, map<string, Text*>> mDefaultTexts;

Shader mShader;
// constructor
TextRenderer();
void Initialize();
// pre-compiles a list of characters from the given font
void LoadFont(string fontPath, unsigned int fontSize, string identifer);
void CreateText(GameState gameState, string identifier, string text, vec2 position, vec3 color, string fontName, float scale, unsigned windowSize = 48, bool scrollableText = true);
void LoadTexts(GameState gameState);
void DrawTexts(GameState gameState);
private:
    unsigned int mVertexArrayObject, mVertexBufferObject;
};

#endif 