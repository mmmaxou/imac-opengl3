#version 330

// Entrées du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

uniform sampler2D uEarthTexture;
uniform sampler2D uCloudTexture;

vec3 blinnPhong() {
  // Couleur=Li(Kd(wi˙N)+Ks(halfVector˙N)shininess)
  vec3 wi = normalize(uLightDir_vs);
  vec3 halfVector = normalize(-vPosition_vs);
  vec3 p1 = uKd*(dot(wi, vNormal_vs));
  vec3 p2 = uKs*pow((dot(halfVector, vNormal_vs)), uShininess);
  vec3 color = uLightIntensity*(p1+p2);
  return color;
}

void main() {
  //fFragColor = texture(uTexture, vTexCoords).xyz;
  //fFragColor = blinnPhong() + texture(uTexture, vTexCoords).xyz;
  vec3 tx1 = texture(uEarthTexture, vTexCoords).xyz;
  vec3 tx2 = texture(uCloudTexture, vTexCoords).xyz;
  fFragColor = (tx1+tx2) * blinnPhong();
}
