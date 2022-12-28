#version 330 core

// vertex shader

layout (location = 0) in vec2 position;

out vec4 fragColor;

uniform mat4 transform;
uniform vec3 color;

void main()
{
    gl_Position = transform * vec4(position, 0.0, 1.0);
    fragColor = vec4(color, 1.0);
}

