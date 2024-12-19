#ifndef TEXT_HPP
#define TEXT_HPP

#include <map>
#include <unordered_map>
#include <string>
#include <glm\glm.hpp>

using namespace glm;
using std::string;
using std::map;

#include "Shader.hpp"
#include "Character.hpp"

class Text {
public:
    string mText;
    vec3 mColor;
    vec2 mPosition;
    float mScale = 1.0f;
    map<char,Character> mCharacters;

    unsigned int mVertexArrayObject,  mVertexBufferObject;
    Shader mShader;

    Text(const string& text, vec2 position, vec3 color, float scale);
    void Draw();
    void UpdateText(const std::string& newText);
    void SetColor(const glm::vec3& color);
    void SetScale(float scale);
};

#endif