#include <cmath>
#include <glimac/glm.hpp> 
#include "glimac/FreeflyCamera.hpp"


namespace glimac {

  const double PI = 3.141592653589;
  const double HALF_PI = PI/2;
  FreeflyCamera::FreeflyCamera()
    : _position(glm::vec3(0.f, 0.f, 0.f)), _fPhi(PI), _fTheta(0)
  {
    computeDirectionVectors();
  }
  
  void FreeflyCamera::computeDirectionVectors() {
    _frontVector = glm::vec3(std::cos(_fTheta) * std::sin(_fPhi),
                             std::sin(_fTheta),
                             std::cos(_fTheta) * std::cos(_fPhi));
    
    _leftVector = glm::vec3(std::sin(_fPhi + HALF_PI),
                            0,
                            std::cos(_fPhi + HALF_PI));
    
    _upVector = glm::cross(_frontVector,
                           _leftVector);
  }
  
  void FreeflyCamera::moveFront(const float &t) {
    _position += t * _frontVector;
    _upVector = glm::cross(_frontVector,
                           _leftVector);
  }
  void FreeflyCamera::moveLeft(const float &t) {
    _position += t * _leftVector; 
    _upVector = glm::cross(_frontVector,
                           _leftVector);
  }  
  void FreeflyCamera::rotateFront(const float &degrees) {
    _fPhi += glm::radians(degrees);
    _frontVector = glm::vec3(std::cos(_fTheta) * std::sin(_fPhi),
                             std::sin(_fTheta),
                             std::cos(_fTheta) * std::cos(_fPhi));
    
    _leftVector = glm::vec3(std::sin(_fPhi + HALF_PI),
                            0,
                            std::cos(_fPhi + HALF_PI));
  }
  void FreeflyCamera::rotateLeft(const float &degrees) {
    _fTheta += glm::radians(degrees);
    _frontVector = glm::vec3(std::cos(_fTheta) * std::sin(_fPhi),
                             std::sin(_fTheta),
                             std::cos(_fTheta) * std::cos(_fPhi));
    
    _leftVector = glm::vec3(std::sin(_fPhi + HALF_PI),
                            0,
                            std::cos(_fPhi + HALF_PI));
  }
  
  glm::mat4 FreeflyCamera::getViewMatrix() const {
    return glm::lookAt(_position, 
                       _position+_frontVector,
                       _upVector);
  }
  
}