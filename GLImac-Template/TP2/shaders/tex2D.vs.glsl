#version 330

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexCoord;

out vec3 vColor;

uniform mat3 uModelMatrix;

void main() {
  vColor = vec3(aVertexCoord, 1);
  vec2 transformed;
  transformed = (uModelMatrix * vec3(aVertexPosition, 1)).xy;
  gl_Position = vec4(transformed, 0, 1);
}
