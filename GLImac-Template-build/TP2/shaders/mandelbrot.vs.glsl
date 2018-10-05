#version 330

layout(location = 0) in vec2 aVertexPosition;

out vec3 vColor;

void main() {
    vColor = vec3(1.0, 0.0, 0.0);
    gl_Position = vec4(aVertexPosition, 0, 1);
}
