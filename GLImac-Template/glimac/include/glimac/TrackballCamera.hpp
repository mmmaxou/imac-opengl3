#include "glm.hpp"

namespace glimac {
  
  class TrackballCamera {
    public:
      TrackballCamera();
      void moveFront(const float &delta);
      void rotateLeft(const float &degrees);
      void rotateRight(const float &degrees);
      glm::mat4 getViewMatrix() const;

    private:
      float _fDistance; // Distane par rapport au centre de la scene
      float _fAngleX; // Angle X autour de la camera
      float _fAngleY; // Angle Y autour de la camera
  };
}