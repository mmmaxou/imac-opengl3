#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;
out vec2 vFragPosition;

mat3 translate(const float tx, const float ty) {
  return mat3(
    vec3(1, 0, 0),
    vec3(0, 1, 0),
    vec3(tx, ty, 1)
  );
}

mat3 scale(const float sx, const float sy) {
  return mat3(
    vec3(sx, 0, 0),
    vec3(0, sy, 0),
    vec3(0, 0, 1)
  );
}

mat3 rotate(const float a) {
  return mat3(
    vec3(cos(a), sin(a), 0),
    vec3(-sin(a), cos(a), 0),
    vec3(0, 0, 1)    
  );
}

void main() {
  vFragPosition = aVertexPosition;
  vFragColor = aVertexColor;
  gl_Position = vec4(aVertexPosition, 0, 1);
};