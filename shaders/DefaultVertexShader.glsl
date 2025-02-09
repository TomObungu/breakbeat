#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader5 : require

layout (location = 0) in vec2 vertexCoordinateAttribute;
layout (location = 1) in vec2 textureCoordinateAttribute;

out vec2 textureCoordinate;

uniform mat4 model;
uniform mat4 projection;
uniform vec2 texturePosition;
uniform float textureScale;

void main()
{
    gl_Position = projection * model * vec4(vertexCoordinateAttribute, 0.0, 1.0);
    textureCoordinate = (textureScale * textureCoordinateAttribute) + texturePosition;
}