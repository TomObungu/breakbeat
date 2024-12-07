#version 460 core

#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader5 : require

out vec4 fragmentColor;
in vec2 textureCoordinate;

layout (bindless_sampler) uniform sampler2D image;
uniform vec3 color;

void main()
{
    fragmentColor = texture(image, (textureCoordinate)) * vec4(color, 1.0);
}
