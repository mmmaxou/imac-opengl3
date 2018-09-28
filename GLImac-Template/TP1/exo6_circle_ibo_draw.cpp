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
  const int segmentNumber = 64;
  const float angleIncrement = glm::pi<float>() / (segmentNumber/2.f);
  float angle = 0.f;  

  // Remplir
  std::vector<Vertex2DColor> vertices;
  
  // Centre
  uint32_t indices[3*segmentNumber];
  vertices.push_back(Vertex2DColor(glm::vec2(0.f, 0.f), 
                                   glm::vec3(1.f, 0.f, 0.f)));
  for (int i=0; i<segmentNumber; i++) {
    vertices.push_back(Vertex2DColor(glm::vec2(rayon*glm::cos(angle), 
                                               rayon*glm::sin(angle)),
                                     glm::vec3(0.f, 1.f, 1.f)));
    angle += angleIncrement;
    indices[3*i] = 0;
    indices[3*i+1] = i+1;
    indices[3*i+2] = i+2;    
    std::cout << indices[3*i] << "," << indices[3*i+1] << "," << indices[3*i+2] << std::endl;
  }
  indices[3*segmentNumber-1] = 1;

  glBufferData(GL_ARRAY_BUFFER, 
               vertices.size() * sizeof(Vertex2DColor), 
               vertices.data(), 
               GL_STATIC_DRAW); // Envoi
  glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind

  // Creation d'un seul IBO
  GLuint ibo;
  glGenBuffers(1, &ibo);
  
  // Bind de l'IBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  // => On remplit l'IBO avec les indices:
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
               segmentNumber*3 * sizeof(uint32_t), 
               indices, 
               GL_STATIC_DRAW);
  
  // Creation d'un seul VAO
  GLuint vao;
  glGenVertexArrays(1, &vao);

  // Bind
  glBindVertexArray(vao);
  // => On bind l'IBO sur GL_ELEMENT_ARRAY_BUFFER; puisqu'un VAO est actuellement bindé,
  // cela a pour effet d'enregistrer l'IBO dans le VAO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

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
      // => On utilise glDrawElements à la place de glDrawArrays
      // Cela indique à OpenGL qu'il doit utiliser l'IBO enregistré dans le VAO
      glDrawElements(GL_TRIANGLES, 
                     segmentNumber*3, 
                     GL_UNSIGNED_INT, 
                     0);
      glBindVertexArray(0);


      // Update the display
      windowManager.swapBuffers();
  }

  // Liberation des ressources
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  return EXIT_SUCCESS;
}
