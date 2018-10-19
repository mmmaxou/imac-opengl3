#version 330

in vec2 vVertexCoord;
out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
//  fFragColor = uColor;
  fFragColor = texture(uTexture, vVertexCoord).xyz;
}
