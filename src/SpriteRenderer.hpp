#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Texture.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"
#include "GameState.hpp"

#include <unordered_map>
#include <map>

using namespace glm;

using std::map;
using std::unordered_map;   
using std::string;

class SpriteRenderer 
{
public:
    // Constructor, Destructor, and other necessary member functions
    SpriteRenderer();
    ~SpriteRenderer();

    // Virtual Draw method for flexibility
    void Initialize();
    Sprite* CreateSprite(GameState, string, Texture&, vec2, vec2, float, vec3, Shader&,bool, vec2 texturePositon = vec2(0,0), float textureScale = 1);
    void DrawSprites(GameState);
    void LoadDefaultSprites(GameState);


    // Hash table to store the sprites currently in use in the render loop
    unordered_map<GameState, map<string, Sprite*>> mCurrentlyRenderedSprites;
    unordered_map<GameState, map<string, Sprite*>> mDefaultSprites;

private:
    // Vertex array object that will be used across all sprites
    GLuint mVertexArrayObject;
    // Hash table to store the defualt positions of the sprites
    // This will be used to restore sprites to their defualt states 
    // This will be when loading different games states
};

#endif // SPRITERENDERER_HPP