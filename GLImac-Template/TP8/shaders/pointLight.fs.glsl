#version 330

// Entrées du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;

uniform sampler2D uTexture;

vec3 blinnPhong() {
  // Couleur=Li(Kd(wi˙N)+Ks(halfVector˙N)shininess)
  vec3 wi = normalize(uLightPos_vs - vPosition_vs);
  vec3 halfVector = normalize(-vPosition_vs);
  vec3 p1 = uKd*(dot(wi, vNormal_vs));
  vec3 p2 = uKs*pow((dot(halfVector, vNormal_vs)), uShininess);
  float d = distance(uLightPos_vs, vPosition_vs);
  vec3 li = uLightIntensity / (d*d);
  vec3 color = li*(p1+p2);
  return color;
}

void main() {
  //fFragColor = texture(uTexture, vTexCoords).xyz;
  //fFragColor = blinnPhong();
  fFragColor = blinnPhong() * texture(uTexture, vTexCoords).xyz;
}
