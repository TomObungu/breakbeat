#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Texture.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"
#include "GameState.hpp"


#include <utility> 
#include <unordered_map>
#include <map>

using namespace glm;

using std::map;
using std::unordered_map;   
using std::string;
using std::vector;

class SpriteRenderer 
{
public:
    // Constructor, Destructor, and other necessary member functions
    SpriteRenderer();
    ~SpriteRenderer();

    void Initialize();
    Sprite* CreateSprite(GameState gameState, string name, Texture& texture, vec2 position, vec2 size, float rotate, vec3 color,Shader& shader, bool perspective, vec2 texturePositon = vec2(0,0), float textureScale = 1);
    void CreateNote(GameState gameState, string name, Texture& texture, vec2 position, vec2 size, float rotate, vec3 color, Shader& shader, bool perspective, vec2 texturePositon = vec2(0, 0), float textureScale = 1);
    void DrawSprites(GameState gameState);
    void LoadDefaultSprites(GameState gameState);


    // Hash table to store the sprites currently in use in the render loop
    unordered_map<GameState, map<string, Sprite*>> mCurrentlyRenderedSprites;
    unordered_map<GameState, map<string, Sprite*>> mDefaultSprites;
    unordered_map<GameState, map<string, Sprite*>> mNoteBuffer;

private:
    GLuint mVertexArrayObject;
    GLuint mVertexArrayObject3D;
    // Vertex array object that will be used across all sprites

    // Hash table to store the defualt positions of the sprites
    // This will be used to restore sprites to their defualt states 
    // This will be when loading different games states
};

#endif // SPRITERENDERER_HPP