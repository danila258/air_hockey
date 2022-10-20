#version 330 core

// vertex shader

layout (location = 0) in vec2 position;

uniform mat4 transform;

void main()
{
  gl_Position = transform * vec4(position, 0.0, 1.0);
}

