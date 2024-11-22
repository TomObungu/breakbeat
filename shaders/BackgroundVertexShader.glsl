#version 460 core
layout(location = 0) in vec3 vertexCoordinateAttribute;
layout(location = 1) in vec2 textureCoordinateAttribute;

out vec2 textureCoordinate;

uniform mat4 model;
uniform mat4 projection;
uniform float time; 

void main() {
    gl_Position = projection * model * vec4(vertexCoordinateAttribute, 1.0);
    textureCoordinate = 2 * textureCoordinateAttribute + vec2(0, time * 0.1); // Adjust speed by changing the multiplier
}
