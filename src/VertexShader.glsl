#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 0) in vec3 color;

uniform mat4 MVP;

out vec3 Color;

void main(){
    gl_Position = MVP * vec4(vertexPosition_modelspace,1);
    Color = color;
}

