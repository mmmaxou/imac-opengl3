#version 330

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexCoord;

out vec3 vColor;

uniform float uTime;

mat3 rotate(const float a) {
  return mat3(
    vec3(cos(a), sin(a), 0),
    vec3(-sin(a), cos(a), 0),
    vec3(0, 0, 1)    
  );
}

void main() {
  vColor = vec3(aVertexCoord, 1);
  vec2 transformed;
  transformed = (rotate(uTime) * vec3(aVertexPosition, 1)).xy;
  gl_Position = vec4(transformed, 0, 1);
}
