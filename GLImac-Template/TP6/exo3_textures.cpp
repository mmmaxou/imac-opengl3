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
#include <glimac/Sphere.hpp> 

using namespace glimac;

int main(int argc, char** argv) {
  // Initialize SDL and open a window
  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGTH = 800;
  SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGTH, "GLImac");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  if(GLEW_OK != glewInitError) {
      std::cerr << glewGetErrorString(glewInitError) << std::endl;
      return EXIT_FAILURE;
  }  
  
  FilePath applicationPath(argv[0]);
  Program program = loadProgram(
      applicationPath.dirPath() + "shaders/3D.vs.glsl",
      applicationPath.dirPath() + "shaders/tex3D.fs.glsl");
  program.use();
  
  /* Load Earth texture */
  std::unique_ptr<Image> imgEarth = loadImage(applicationPath.dirPath() + "../../GLImac-Template/assets/textures/EarthMap.jpg");
  if ( imgEarth == NULL ) std::cout << "Earth Image Not Loaded" << std::endl;
  /* Load Moon texture */
  std::unique_ptr<Image> imgMoon = loadImage(applicationPath.dirPath() + "../../GLImac-Template/assets/textures/MoonMap.jpg");
  if ( imgMoon == NULL ) std::cout << "Moon Image Not Loaded" << std::endl;

  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
  
  
  /* 3_ Récupération des variables uniformes */
  GLint uMVPMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
  GLint uMVMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");
  GLint uNormalMatrixLocation = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
  GLint uTextureLocation = glGetUniformLocation(program.getGLId(), "uTexture");

  /*********************************
   * HERE SHOULD COME THE INITIALIZATION CODE
   *********************************/
  /* 1_ Construction de la sphere */
  Sphere sphere(1, 32, 32);
  
  /* 2_ Création du VBO et du VAO */
  GLuint vbo, vao;
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER,
               sphere.getVertexCount() * sizeof(ShapeVertex),
               sphere.getDataPointer(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  glBindVertexArray(vao);
  const GLuint VERTEX_ATTR_POSITION = 0;
  const GLuint VERTEX_ATTR_NORMAL = 1;
  const GLuint VERTEX_ATTR_COORDS = 2;
  glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
  glEnableVertexAttribArray(VERTEX_ATTR_COORDS);  
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  
  glVertexAttribPointer(
    VERTEX_ATTR_POSITION, // index
    3, // size
    GL_FLOAT, // type
    GL_FALSE, // normalized
    sizeof(ShapeVertex), // stride
    (const GLvoid*) offsetof(ShapeVertex, position) // pointer
  );
  
  glVertexAttribPointer(
    VERTEX_ATTR_NORMAL, // index
    3, // size
    GL_FLOAT, // type
    GL_FALSE, // normalized
    sizeof(ShapeVertex), // stride
    (const GLvoid*) offsetof(ShapeVertex, normal) // pointer
  );
  
  glVertexAttribPointer(
    VERTEX_ATTR_COORDS, // index
    2, // size
    GL_FLOAT, // type
    GL_FALSE, // normalized
    sizeof(ShapeVertex), // stride
    (const GLvoid*) offsetof(ShapeVertex, texCoords) // pointer
  );
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);  
  glBindVertexArray(0);
  
  /* 4_ Activation de la detection de la profondeur */
  glEnable(GL_DEPTH_TEST);
  
  /* 5_ Création des matrices de Projection, MV et Normales */
  glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
  
  /* 6_ Calcul de la ProjMatrix */
  ProjMatrix = glm::perspective(glm::radians(70.0f), // Angle vertical de vue
                   (float) (WINDOW_WIDTH / WINDOW_HEIGTH), // Ratio de la fenetre
                   0.1f, // Near
                   100.f); // Far
  
  /* 7_ Calcul de la MVMatrix */
  MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));
    
  /* 8_ Calcul de la NormalMatrix */
  NormalMatrix = glm::transpose( glm::inverse( MVMatrix ) );
  
  /* 12_ Autres lunes */
  std::vector<glm::vec3> rotationAxes;
  for (int i=0; i<32; i++) {
    glm::vec3 r = glm::sphericalRand(2.0f);
//    std::cout << r << std::endl;
    rotationAxes.push_back(r);
  } 
  
  // TEXTURES On
  GLuint textures[2];
  glGenTextures(2, textures);
  
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glTexImage2D(GL_TEXTURE_2D, // Target
               0, // Mipmap level
               GL_RGBA, // Internal Format
               imgEarth->getWidth(), // Width
               imgEarth->getHeight(), // Height
               0, // Border
               GL_RGBA, // Format
               GL_FLOAT, // Type
               imgEarth->getPixels() // Value
              );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  glBindTexture(GL_TEXTURE_2D, textures[1]);
  glTexImage2D(GL_TEXTURE_2D, // Target
               0, // Mipmap level
               GL_RGBA, // Internal Format
               imgMoon->getWidth(), // Width
               imgMoon->getHeight(), // Height
               0, // Border
               GL_RGBA, // Format
               GL_FLOAT, // Type
               imgMoon->getPixels() // Value
              );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  // TEXTURE Off


  // Application loop:
  bool done = false;
  float time = 0.0f;
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);

    /* 9_ Envoi des matrices au GPU */
    /* POUR LA LUNE PRINCIPALE */
    MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));
    MVMatrix = glm::rotate(MVMatrix,
                           windowManager.getTime(),
                           glm::vec3(0.f, 1.f, 0.f)); // Rotation
    
    // MVP
    // Texture
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glUniform1i(uTextureLocation, 0);
    glUniformMatrix4fv(uMVPMatrixLocation, // Location
                       1, // Count
                       GL_FALSE, // Transpose
                       glm::value_ptr(ProjMatrix * MVMatrix)); // Value
    // MV    
    glUniformMatrix4fv(uMVMatrixLocation, // Location
                       1, // Count
                       GL_FALSE, // Transpose
                       glm::value_ptr(MVMatrix)); // Value
    // Normal
    glUniformMatrix4fv(uNormalMatrixLocation, // Location
                       1, // Count
                       GL_FALSE, // Transpose
                       glm::value_ptr(NormalMatrix)); // Value
    
    /* 10_ Dessin de la LUNE PRINCIPALE */
    
    // Texture
    glUniform1i(uTextureLocation, 0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    
    glDrawArrays(GL_TRIANGLES, 
                 0,
                 sphere.getVertexCount());
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Texture
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    
    for ( int i=0; i<32; i++) {
      /* 11_ Dessin d'une autre lune */
      // Translation
      MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); 
      // Translation * Rotation
      MVMatrix = glm::rotate(MVMatrix,
                             windowManager.getTime(),
                             glm::cross(glm::vec3(1.f, 1.f, 1.f), rotationAxes[i]) ); 
      // Translation * Rotation * Translation
      MVMatrix = glm::translate(MVMatrix, rotationAxes[i]); 
      // Translation * Rotation * Translation * Scale
      MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2));    
      // MVP
      glUniformMatrix4fv(uMVPMatrixLocation, // Location
                         1, // Count
                         GL_FALSE, // Transpose
                         glm::value_ptr(ProjMatrix * MVMatrix)); // Value
      // MV    
      glUniformMatrix4fv(uMVMatrixLocation, // Location
                         1, // Count
                         GL_FALSE, // Transpose
                         glm::value_ptr(MVMatrix)); // Value
      glDrawArrays(GL_TRIANGLES, 
                   0,
                   sphere.getVertexCount());
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    // Update the display
    windowManager.swapBuffers();
  }

  // Liberation des ressources
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glDeleteTextures(2, textures);
  return EXIT_SUCCESS;
}
