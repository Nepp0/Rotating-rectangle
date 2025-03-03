#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;

out vec3 ourColor;
out vec2 dTexture;
uniform vec4 uniPos;
uniform mat4 transform;
void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    //gl_Position += vec4(uniPos.x,0,0.0,0.0);
    ourColor = aColor;
    dTexture = aTexture;
}
