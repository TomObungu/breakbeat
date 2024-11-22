#version 460 core
out vec4 fragmentColor;
in vec2 textureCoordinate;

uniform sampler2D image;
uniform vec3 color;

void main()
{
    fragmentColor = texture(image, textureCoordinate) * vec4(color, 1.0);
}
