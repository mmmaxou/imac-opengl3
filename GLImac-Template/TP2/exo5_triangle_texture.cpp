#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <vector>
#include <math.h>
#include <glimac/Program.hpp> 
#include <glimac/FilePath.hpp> 
#include <glimac/glm.hpp> 
#include <glimac/Image.hpp> 

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

glm::mat3 translate(const float tx, const float ty) {
  return glm::mat3(
    glm::vec3(1, 0, 0),
    glm::vec3(0, 1, 0),
    glm::vec3(tx, ty, 1)
  );
}

glm::mat3 scale(const float sx, const float sy) {
  return glm::mat3(
    glm::vec3(sx, 0, 0),
    glm::vec3(0, sy, 0),
    glm::vec3(0, 0, 1)
  );
}

glm::mat3 rotate(const float a) {
  return glm::mat3(
    glm::vec3(cos(a), sin(a), 0),
    glm::vec3(-sin(a), cos(a), 0),
    glm::vec3(0, 0, 1)    
  );
}

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
  std::unique_ptr<Image> imageTriforce = loadImage(applicationPath.dirPath() + "../../GLImac-Template/assets/textures/triforce.png");
  if ( imageTriforce == NULL ) std::cout << "Image Not Loaded" << std::endl;
  
  Program program = loadProgram(
      applicationPath.dirPath() + "shaders/tex2D.vs.glsl",
      applicationPath.dirPath() + "shaders/tex2D.fs.glsl");
  program.use();
  
  GLint uModelMatrixLocation = glGetUniformLocation(program.getGLId(), "uModelMatrix");
  GLint uColorLocation = glGetUniformLocation(program.getGLId(), "uColor");
  GLint uTextureLocation = glGetUniformLocation(program.getGLId(), "uTexture");
  std::cout << "GL Uniform Location Matrix : " << uColorLocation << std::endl;
  std::cout << "GL Uniform Location Color: " << uColorLocation << std::endl;
  std::cout << "GL Uniform Location Texture: " << uTextureLocation << std::endl;
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
                                glm::vec2(0.f, 1.f)) );  
  vertices.push_back(Vertex2DUV(glm::vec2(1.f, -1.f),
                                glm::vec2(1.f, 1.f)) );
  vertices.push_back(Vertex2DUV(glm::vec2(0.f, 1.f), 
                                glm::vec2(0.5f, 0.f)) );
  
  
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
  
  // TEXTURES On
  GLuint textures[1];
  glGenTextures(1, textures);
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glTexImage2D(GL_TEXTURE_2D, // Target
               0, // Mipmap level
               GL_RGBA, // Internal Format
               imageTriforce->getWidth(), // Width
               imageTriforce->getHeight(), // Height
               0, // Border
               GL_RGBA, // Format
               GL_FLOAT, // Type
               imageTriforce->getPixels() // Value
              );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);  
  // TEXTURE Off

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

    // Bind du VAO et dessin
    glBindVertexArray(vao);
    
    // Modification du uTime
    time += 0.02;
    glm::mat3 modelMatrix;
    
    // Texture
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glUniform1i(uTextureLocation, 0);
    
    // Triangle 1
    modelMatrix = rotate(time) * translate(0.5f, 0.5f) * rotate(-time) * scale(0.25f, 0.25f);
    glUniformMatrix3fv(uModelMatrixLocation, // Location
                       1, // Count
                       GL_FALSE, // Transpose
                       glm::value_ptr(modelMatrix)); // Value
    glDrawArrays(GL_TRIANGLES, 
                 0,
                 vertices.size() * 3);
    
    // Triangle 2
    modelMatrix = rotate(time) * translate(-0.5f, 0.5f) * rotate(-time) * scale(0.25f, 0.25f);
    glUniformMatrix3fv(uModelMatrixLocation, // Location
                       1, // Count
                       GL_FALSE, // Transpose
                       glm::value_ptr(modelMatrix)); // Value
    glDrawArrays(GL_TRIANGLES, 
                 0,
                 vertices.size() * 3);
    
    // Triangle 3
    modelMatrix = rotate(time) * translate(0.5f, -0.5f) * rotate(time) * scale(0.25f, 0.25f);
    glUniformMatrix3fv(uModelMatrixLocation, // Location
                       1, // Count
                       GL_FALSE, // Transpose
                       glm::value_ptr(modelMatrix)); // Value
    glDrawArrays(GL_TRIANGLES, 
                 0,
                 vertices.size() * 3);
    
    // Triangle 4
    modelMatrix = rotate(time) * translate(-0.5f, -0.5f) * rotate(time) * scale(0.25f, 0.25f);
    glUniformMatrix3fv(uModelMatrixLocation, // Location
                       1, // Count
                       GL_FALSE, // Transpose
                       glm::value_ptr(modelMatrix)); // Value
    glDrawArrays(GL_TRIANGLES, 
                 0,
                 vertices.size() * 3);
    
    
    

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    // Update the display
    windowManager.swapBuffers();
  }
  
  // Liberation des ressources
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glDeleteTextures(1, textures);
  return EXIT_SUCCESS;
}
