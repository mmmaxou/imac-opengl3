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

struct Vertex2DUV {
  
  glm::vec2 position;
  glm::vec2 coord;
    
  Vertex2DUV(const glm::vec2 &pos,
                const glm::vec2 &c) {
    position.x = pos.x;
    position.y = pos.y;
    coord.x = c.x;
    coord.y = c.y;
  };
};

int main(int argc, char** argv) {
  // Initialize SDL and open a window
  SDLWindowManager windowManager(800, 600, "GLImac");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  if(GLEW_OK != glewInitError) {
    std::cerr << glewGetErrorString(glewInitError) << std::endl;
    return EXIT_FAILURE;
  }
  
  
  FilePath applicationPath(argv[0]);
  Program program = loadProgram(
      applicationPath.dirPath() + "shaders/tex2D.vs.glsl",
      applicationPath.dirPath() + "shaders/tex2D.fs.glsl");
  program.use();
  
  GLint uTimeLocation = glGetUniformLocation(program.getGLId(), "uTime");
  std::cout << "GL Uniform Location : " << uTimeLocation << std::endl;
  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

  /*********************************
   * HERE SHOULD COME THE INITIALIZATION CODE
   *********************************/
  
  // VBO On
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  
  std::vector<Vertex2DUV> vertices;
  vertices.push_back(Vertex2DUV(glm::vec2(-1.f, -1.f), 
                                glm::vec2(0.f, 0.f)) );  
  vertices.push_back(Vertex2DUV(glm::vec2(1.f, -1.f),
                                glm::vec2(0.f, 0.f)) );
  vertices.push_back(Vertex2DUV(glm::vec2(0.f, 1.f), 
                                glm::vec2(0.f, 0.f)) );
  
  
  glBufferData(GL_ARRAY_BUFFER,
               vertices.size()*sizeof(Vertex2DUV),
               vertices.data(),
               GL_STATIC_DRAW);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // VBO Off
  
  // VAO On
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  const GLuint VERTEX_ATTR_POSITION = 0;
  const GLuint VERTEX_ATTR_COORDINATES = 1;
  glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  glEnableVertexAttribArray(VERTEX_ATTR_COORDINATES);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);  
  glVertexAttribPointer(
      VERTEX_ATTR_POSITION, // index
      2, // size
      GL_FLOAT, // type
      GL_FALSE, // normalized
      sizeof(Vertex2DUV), // stride
      (const GLvoid*) offsetof(Vertex2DUV, position) // pointer
  ); 
  glVertexAttribPointer(
      VERTEX_ATTR_COORDINATES, // index
      2, // size
      GL_FLOAT, // type
      GL_FALSE, // normalized
      sizeof(Vertex2DUV), // stride
      (const GLvoid*) offsetof(Vertex2DUV, coord) // pointer
  );  
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  // VAO Off 

  // Application loop:
  float time = 0.0f;
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
    
    // Modification du uTime
    time += 0.01;
    glUniform1f( uTimeLocation, time);

    // Bind du VAO et dessin
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 
                 0,
                 vertices.size() * 3);
    glBindVertexArray(0);

    // Update the display
    windowManager.swapBuffers();
  }

  return EXIT_SUCCESS;
}
