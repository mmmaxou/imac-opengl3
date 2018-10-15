#version 330

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexCoord;

out vec3 vColor;

void main() {
  vColor = vec3(aVertexCoord, 1);
  gl_Position = vec4(aVertexPosition, 0, 1);
}
