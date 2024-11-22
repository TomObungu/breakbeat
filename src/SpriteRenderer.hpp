#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.hpp"
#include "Shader.hpp"

using namespace glm;

class SpriteRenderer {
public:
    // Constructor, Destructor, and other necessary member functions
    SpriteRenderer(Shader& shader);
    virtual ~SpriteRenderer();

    // Virtual Draw method for flexibility
    virtual void Draw(Texture &texture, vec2 position, vec2 size, float rotate = 0.0f, vec3 color = vec3(1.0f));
    void Initialize();
    void UseShader(Shader&);
protected:
    Shader mShader;
    GLuint mVertexArrayObject;
};

#endif // SPRITERENDERER_HPP
