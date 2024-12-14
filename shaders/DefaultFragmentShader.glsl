#version 460 core

#extension GL_ARB_bindless_texture : require // Include bindless texture extensions
#extension GL_ARB_gpu_shader5 : require // Allow the textures reference to be accessed directly

in vec2 textureCoordinate;

out vec4 fragmentColor;
layout (bindless_sampler) uniform sampler2D image; // Allow the texture uniform to be stored as two 32 bit unsinged integers
uniform vec3 color;

void main()
{
    fragmentColor = texture(image, (textureCoordinate)) * vec4(color, 1.0);
}