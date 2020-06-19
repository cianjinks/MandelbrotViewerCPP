#version 410 core

layout(location = 0) in vec2 position;

out vec4 v_Pos;
void main() {
    gl_Position = vec4(position, 0, 1.0);
    v_Pos = vec4(position, 0, 1.0);
}