#version 330 core

in vec2 vFragPosition;
out vec3 fFragColor;

vec2 complexSqr(vec2 z) {
  float x = (z.x * z.x) - (z.y * z.y);
  float y = 2 * z.x * z.y;
  return vec2(x, y);
}

vec2 nextTerm(vec2 z) {
  return complexSqr(z) + vFragPosition;
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
  bool isMandelbrot = true;  
  vec2 terme = vFragPosition;
  int N = 30;  
  
  for ( int i=0; i<N; i++) {
    terme = nextTerm( terme );
    if ( length(terme) > 2) {
      isMandelbrot = false;
      fFragColor = hsv2rgb( vec3( (float(i)/N), 0.8, 0.8 ) );
      break;
    }
  }

  
  if ( isMandelbrot ) {
    fFragColor = vec3(1.0, 1.0, 1.0);
  }
}
