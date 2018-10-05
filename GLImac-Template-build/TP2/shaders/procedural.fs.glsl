#version 330 core

in vec3 vFragColor;
in vec2 vFragPosition;

out vec3 fFragColor;

void main() {
  
  vec2 P = vFragPosition;
  // 1_Liseré :
  //float coeff = length(fract(5.0 * P));
  
  // 2_Liseré_dégradé
  //float coeff = length(abs(fract(5.0 * P) * 2.0 - 1.0));
  
  // 3_Carré_Dégradé
  //float coeff = mod(floor(10.0 * P.x) + floor(10.0 * P.y), 2.0);
  
  // 4_Petits_Ronds
  //float coeff = smoothstep(0.3, 0.32, length(fract(5.0 * P) - 0.5));
  
  // 5_Walls
  float coeff = smoothstep(0.4, 0.5, max(abs(fract(8.0 * P.x - 0.5 * mod(floor(8.0 * P.y), 2.0)) - 0.5), abs(fract(8.0 * P.y) - 0.5)));
  
  fFragColor = coeff * vFragColor;
};