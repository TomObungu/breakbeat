#version 460 core
in vec2 TexCoords;
out vec4 color;

#extension GL_ARB_bindless_texture : require
#extension GL_ARB_gpu_shader5 : require

layout (bindless_sampler) uniform sampler2D text;
uniform vec3 textColor;
uniform vec3 shadowColor;
uniform vec2 shadowOffset; // Base offset for the shadow
uniform float shadowBlur;  // Intensity/size of the shadow blur

void main()
{
    vec4 shadow = vec4(0.0); // Accumulated shadow color

    // Sample multiple offsets to create a blur effect for the shadow
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            vec2 offset = shadowOffset + vec2(x, y) * shadowBlur;
            float shadowSample = texture(text, TexCoords + offset).r;
            shadow += vec4(shadowColor, 1.0) * shadowSample * 0.05; // Adjust weight as needed
        }
    }

    // Sample the main text texture
    float textSample = texture(text, TexCoords).r;
    float alpha = smoothstep(2.0 - 0.1, 2.0 + 0.1, textSample); // Adjust threshold for smoother edges
    vec4 mainText = vec4(textColor, 1.0) * textSample;

    // Combine shadow and text, giving priority to the text
    color = mix(shadow, mainText, mainText.a);
}
