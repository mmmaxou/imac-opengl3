#version 330 core

in vec3 vFragColor;
in vec2 vFragPosition;

out vec3 fFragColor;

void main() {
  
  
  float dist = distance(vFragPosition, vec2(0.0, 0.0));
  float alpha = 3.1;
  float beta = 25.0;
  float sqrtDistBeta = dist * dist * (-beta);
  float coeff = alpha * exp(sqrtDistBeta);
  /*
    float coeff2 = alpha * dist;
    float coeff = 1 / (1.0 + coeff1 + coeff2);
  */
  fFragColor = coeff * vFragColor;
};