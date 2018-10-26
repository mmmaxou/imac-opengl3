#include "glm.hpp"

namespace glimac {
  
  class FreeflyCamera {
    public:
      FreeflyCamera();
      void moveFront(const float &t);
      void moveLeft(const float &t);
      void rotateFront(const float &degrees);
      void rotateLeft(const float &degrees);
      glm::mat4 getViewMatrix() const;

    private:
      glm::vec3 _position; // Position de la camera
      float _fPhi; // Coord du vecteur sphérique F
      float _fTheta; // Coord du vecteur sphérique F
      glm::vec3 _frontVector; // Vecteur F
      glm::vec3 _leftVector; // Vecteur L
      glm::vec3 _upVector; // Vecteur U
      
      void computeDirectionVectors();
  };
}