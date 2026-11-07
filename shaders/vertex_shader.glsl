#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform mat4 u_Viewprojection;

out vec2 TexCoords;

void main() {
    TexCoords = aTexCoords; 
    gl_Position = u_Viewprojection * vec4(aPos, 1.0);
}