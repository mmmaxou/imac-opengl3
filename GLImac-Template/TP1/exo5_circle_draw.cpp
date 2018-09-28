#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <vector>
#include <math.h>
#include <glimac/Program.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/glm.hpp> 

using namespace glimac;

struct Vertex2DColor {
  
  glm::vec2 position;
  glm::vec3 color;
  
  Vertex2DColor() {
    position.x = 0;
    position.y = 0;
  };
  
  Vertex2DColor(const glm::vec2 &pos,
                const glm::vec3 &col) {
    position.x = pos.x;
    position.y = pos.y;
    color.r = col.r;
    color.g = col.g;
    color.b = col.b;
  };
  
  Vertex2DColor(const float posX,
                const float posY, 
                const float r,
                const float g,
                const float b) {
    position.x = posX;
    position.y = posY;
    color.r = r;
    color.g = g;
    color.b = b;
  };
};


int main(int argc, char** argv) {
  // Initialize SDL and open a window
  SDLWindowManager windowManager(800, 800, "GLImac");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  if(GLEW_OK != glewInitError) {
      std::cerr << glewGetErrorString(glewInitError) << std::endl;
      return EXIT_FAILURE;
  }

  FilePath applicationPath(argv[0]);
  Program program = loadProgram(
      applicationPath.dirPath() + "shaders/triangle.vs.glsl",
      applicationPath.dirPath() + "shaders/triangle.fs.glsl");
  program.use();    

  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

  /*********************************
   * HERE SHOULD COME THE INITIALIZATION CODE
   *********************************/

  // Creation d'un seul VBO
  GLuint vbo;
  glGenBuffers(1, &vbo);

  // Bind
  glBindBuffer(GL_ARRAY_BUFFER, vbo);  
  
  // Parametres du cercles
  const float rayon = 0.8f;
  const int segmentNumber = 16;
  const float angleIncrement = glm::pi<float>() / (segmentNumber/2.f);
  float angle = 0.f;  

  // Remplir
  std::vector<Vertex2DColor> vertices;
  vertices.empty();
  for ( int i=segmentNumber; i>0; i--) {    
    float x = 0.f, y = 0.f;
    
    x = rayon*glm::cos(angle);
    y = rayon*glm::sin(angle);
    vertices.push_back(Vertex2DColor(glm::vec2(x, y),
                                     glm::vec3(0.f, 1.f, 1.f)));
    
    x = rayon*glm::cos(angle + angleIncrement);
    y = rayon*glm::sin(angle + angleIncrement);
    vertices.push_back(Vertex2DColor(glm::vec2(x, y), 
                                     glm::vec3(0.f, 1.f, 1.f)));
    
    x = 0.f;
    y = 0.f;
    vertices.push_back(Vertex2DColor(glm::vec2(x, y), 
                                     glm::vec3(1.f, 0.f, 0.f)));
    
    angle += angleIncrement;
  }

  // Envoi
  glBufferData(GL_ARRAY_BUFFER, 
               vertices.size() * sizeof(Vertex2DColor), 
               vertices.data(), 
               GL_STATIC_DRAW);

  // Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Creaton d'un seul VAO
  GLuint vao;
  glGenVertexArrays(1, &vao);

  // Bind
  glBindVertexArray(vao);

  // Activation
  // 3 et 8 sont tirés des shaders
  const GLuint VERTEX_ATTR_POSITION = 3;
  const GLuint VERTEX_ATTR_COLOR = 8;
  glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(
      VERTEX_ATTR_POSITION, // index
      2, // size
      GL_FLOAT, // type
      GL_FALSE, // normalized
      sizeof(Vertex2DColor), // stride
      (const GLvoid*) offsetof(Vertex2DColor, position) // pointer
  );
  glVertexAttribPointer(
      VERTEX_ATTR_COLOR, // index
      3, // size
      GL_FLOAT, // type
      GL_FALSE, // normalized
      sizeof(Vertex2DColor), // stride
      (const GLvoid*) offsetof(Vertex2DColor, color) // pointer
  );
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Unbind
  glBindVertexArray(0);


  // Maintenant on dessine
  // Application loop:
  bool done = false;
  while(!done) {
      // Event loop:
      SDL_Event e;
      while(windowManager.pollEvent(e)) {
          if(e.type == SDL_QUIT) {
              done = true; // Leave the loop after this iteration
          }
      }

      /*********************************
       * HERE SHOULD COME THE RENDERING CODE
       *********************************/

      glClear(GL_COLOR_BUFFER_BIT);

      // Bind du VAO et dessin
      glBindVertexArray(vao);
      glDrawArrays(GL_TRIANGLES, 0, vertices.size() * 3);
      glBindVertexArray(0);


      // Update the display
      windowManager.swapBuffers();
  }

  // Liberation des ressources
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  return EXIT_SUCCESS;
}