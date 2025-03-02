#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 dTexture;
uniform vec4 uniColor;
uniform sampler2D uniTexture;
uniform sampler2D uniTexture2;
uniform float opacity;

void main()
{
    FragColor = mix(texture(uniTexture, dTexture), texture(uniTexture2, dTexture), opacity) * vec4(ourColor, 1.0f);
    FragColor += uniColor;
}
