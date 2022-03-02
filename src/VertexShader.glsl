#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex;

uniform mat4 MVP;
out vec2 TexCoords;
out vec3 Color;

void main(){
    TexCoords = tex;
    gl_Position = MVP * vec4(vertexPosition_modelspace,1);
}
