#version 460 core
#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader5 : require

layout (location = 0) in vec3 vertexCoordinateAttribute; // Correctly defined for 3D vertices
layout (location = 1) in vec2 textureCoordinateAttribute;

out vec2 textureCoordinate;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 texturePosition;
uniform float textureScale;

void main()
{
    gl_Position = projection * view * model * vec4(vertexCoordinateAttribute, 1.0f);
    textureCoordinate = (textureScale * textureCoordinateAttribute) + texturePosition;
    textureCoordinate = vec2(-textureCoordinate.x, -textureCoordinate.y);
}
