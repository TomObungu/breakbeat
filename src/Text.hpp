#ifndef TEXT_HPP
#define TEXT_HPP

#include <map>
#include <unordered_map>
#include <string>
#include <glm\glm.hpp>
#include "SDL.h"

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
    void Update(float deltaTime);
    void SetColor(const glm::vec3& color);
    void SetScale(float scale);
    void SetDarken(bool enable, float darkenTime = 1.0f);  // New method to start/stop darkening
    
    void Darken();  // Existing method to handle darkening process
    // Procedure to brighten the sprutes color from the darkened sate over time
    void SetBrighten(bool enable, float invertTime = 1.0f);  // New method to start/stop inverting
    void Brighten();  // Existing method to handle inversion (lightening
    void SetScale(bool enable, float targetScale, float scaleTime = 1.0f, bool looping = false);
    const string& GetText();
private:
    bool mIsScaling = false;
    float mStartScale = 1.0f;
    float mTargetScale = 1.0f;
    float mScaleTime;
    float mScaleStartTime;
    bool mIsLoopScaling;

    bool mHasUpdated;

    float mDarkenStartTime = 0.0f;
    float mBrightenStartTime = 0.0f;
    float mDarkenTime = 1.0f;
    float mBrightenTime = 1.0f;

    bool mDarkening = false;
    bool mBrightening = false;

    vec3 mOriginalColor;
    vec3 mDarkenedColor;

    // State varible to determine when the varible is dark or bright
    bool mDarkened = false;
    bool mBrightened = false;
};

#endif