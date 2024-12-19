#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include <ft2build.h>
#include <freetype/freetype.h>
#include FT_FREETYPE_H

#include "TextRenderer.hpp"
#include "ResourceManager.hpp"

TextRenderer::TextRenderer()
{
}

void TextRenderer::Initialize()
{
    std::cout<<"Initializing text renderer"<<'\n';
    // load and configure shader
    this->mShader = ResourceManager::GetShader("text");
    this->mShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<float>(1920), static_cast<float>(1080), 0.0f), true);
    this->mShader.SetInteger("text", 0);
    this->mShader.SetVector3f("shadowColor", glm::vec3(0.0f, 0.0f, 0.0f)); // Black shadow
    this->mShader.SetVector2f("shadowOffset", glm::vec2(0.005f, -0.005f)); // Offset slightly down and right
    this->mShader.SetFloat("shadowBlur", 0.002f); // Adjust for more/less blur

    // configure VAO/VBO for texture quads
    glGenVertexArrays(1, &this->mVertexArrayObject);
    glGenBuffers(1, &this->mVertexBufferObject);
    glBindVertexArray(this->mVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mFonts.clear();
}

void TextRenderer::LoadFont(string fontPath, unsigned int fontSize, string identifer) 
{
        std::cout<<"Loading font!"<<'\n';
        // Load font using FreeType
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            return;
        }

        FT_Face face;
        if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
            std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return;
        }

        FT_Set_Pixel_Sizes(face, 0, fontSize);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

        std::map<char, Character> characters;

        for (GLubyte c = 0; c < 128; c++) {
            // Load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cerr << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // Generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D
            (
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );

            // Set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Store character
            Character character = 
            {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };

            characters.insert(std::pair<char, Character>(c, character));
        }

        mFonts[identifer] = characters;

        glBindTexture(GL_TEXTURE_2D, 0);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
}

void TextRenderer::CreateText(GameState gameState, string identifier, string text, glm::vec2 position, vec3 color, string fontName) 
{
    std::cout<<"Creating new text!"<<'\n';
    auto textObj = new Text(text, position, vec3(1.0f), 5.0f);
    textObj->mVertexArrayObject = this->mVertexArrayObject;
    textObj->mVertexBufferObject = this->mVertexBufferObject;
    textObj->mShader = this->mShader;
    textObj->mCharacters = mFonts[fontName];
    textObj->mColor;
    mDefaultTexts[gameState][identifier] = textObj;
}

void TextRenderer::DrawTexts(GameState gameState)
{
    // Iterate through each text in text hash table and call its draw function
    for (auto& [key, text] : mCurrentlyRenderedTexts[gameState])
    {
        text->Draw(); // Draw the text
    }
}

void TextRenderer::LoadTexts(GameState gameState)
{
    // Iterate through each text and copy it to the text hash table
    for (auto& [key, text] : mDefaultTexts[gameState])
    {
        // Use the copy constructor to create a copy of the sprite
        mCurrentlyRenderedTexts[gameState][key] = text;
    }
}