#version 460 core
layout (location = 0) in vec2 vertexCoordinateAttribute;
layout (location = 1) in vec2 textureCoordinateAttribute;

out vec2 textureCoordinate;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(vertexCoordinateAttribute, 0.0, 1.0);
    textureCoordinate = textureCoordinateAttribute;
}
