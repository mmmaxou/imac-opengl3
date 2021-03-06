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
#include <glimac/FreeflyCamera.hpp> 

using namespace glimac;

struct EarthProgram {
  Program m_Program;
  
  GLint uMVPMatrix;
  GLint uMVMatrix;
  GLint uNormalMatrix;
  GLint uEarthTexture;
  GLint uCloudTexture;
  
  EarthProgram( const FilePath& applicationPath ) :
    m_Program(loadProgram(
      applicationPath.dirPath() + "shaders/3D.vs.glsl",
      applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl")) 
    {
      uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
      uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
      uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
      uEarthTexture = glGetUniformLocation(m_Program.getGLId(), "uEarthTexture");
      uCloudTexture = glGetUniformLocation(m_Program.getGLId(), "uCloudTexture");
    }  
};

struct MoonProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    MoonProgram( const FilePath& applicationPath ):
        m_Program(loadProgram(
          applicationPath.dirPath() + "shaders/3D.vs.glsl",
          applicationPath.dirPath() + "shaders/tex3D.fs.glsl")) 
    {
      uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
      uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
      uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
      uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};


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
  EarthProgram earthProgram(applicationPath);
  MoonProgram moonProgram(applicationPath);  
  
  /* Load Earth texture */
  std::unique_ptr<Image> imgEarth = loadImage(applicationPath.dirPath() + "../../GLImac-Template/assets/textures/EarthMap.jpg");
  if ( imgEarth == NULL ) std::cout << "Earth Image Not Loaded" << std::endl;
  
  /* Load Moon texture */
  std::unique_ptr<Image> imgMoon = loadImage(applicationPath.dirPath() + "../../GLImac-Template/assets/textures/MoonMap.jpg");
  if ( imgMoon == NULL ) std::cout << "Moon Image Not Loaded" << std::endl;
  
  /* Load Clouds texture */
  std::unique_ptr<Image> imgClouds = loadImage(applicationPath.dirPath() + "../../GLImac-Template/assets/textures/CloudMap.jpg");
  if ( imgClouds == NULL ) std::cout << "Cloud Image Not Loaded" << std::endl;
  
  

  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
    
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
  
  /* 5-8_ Création des matrices de Projection, MV et Normales */
  glm::mat4 ProjMatrix, MVMatrix, NormalMatrix, globalMVMatrix;
  ProjMatrix = glm::perspective(glm::radians(70.0f), // Angle vertical de vue
                   (float) (WINDOW_WIDTH / WINDOW_HEIGTH), // Ratio de la fenetre
                   0.1f, // Near
                   100.f); // Far
  
  /* Création de la camera */
  FreeflyCamera camera;  
  
  /* 12_ Autres lunes */
  std::vector<glm::vec3> rotationAxes;
  std::vector<glm::vec3> translationValues;
  const float dMin = -3.0f;
  const float dMax = 3.0f;
  for (int i=0; i<32; i++) {    
    glm::vec3 r = glm::sphericalRand(1.0f);
    rotationAxes.push_back(r);
    translationValues.push_back(glm::vec3(glm::linearRand(dMin, dMax), glm::linearRand(dMin, dMax), glm::linearRand(dMin, dMax)));
  }
  
  // Chargement des textures
  GLuint textures[3];
  glGenTextures(3, textures);
  
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
  
  glBindTexture(GL_TEXTURE_2D, textures[2]);
  glTexImage2D(GL_TEXTURE_2D, // Target
               0, // Mipmap level
               GL_RGBA, // Internal Format
               imgClouds->getWidth(), // Width
               imgClouds->getHeight(), // Height
               0, // Border
               GL_RGBA, // Format
               GL_FLOAT, // Type
               imgClouds->getPixels() // Value
              );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  // End Chargement des textures
  bool KEY_UP_PRESSED = false;
  bool KEY_DOWN_PRESSED = false;
  bool KEY_LEFT_PRESSED = false;
  bool KEY_RIGHT_PRESSED = false;

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
      
      switch(e.type) {

          /* Touche clavier DOWN */
        case SDL_KEYDOWN: 
          {
            if (e.key.keysym.sym == SDLK_z 
                || e.key.keysym.sym == SDLK_UP) {
              KEY_UP_PRESSED = true;
            } 
            if (e.key.keysym.sym == SDLK_s 
                       || e.key.keysym.sym == SDLK_DOWN) {
              KEY_DOWN_PRESSED = true;
            }
            if (e.key.keysym.sym == SDLK_q 
                       || e.key.keysym.sym == SDLK_LEFT) {
              KEY_LEFT_PRESSED = true;
            }
            if (e.key.keysym.sym == SDLK_d 
                       || e.key.keysym.sym == SDLK_RIGHT) {
              KEY_RIGHT_PRESSED = true;
            }
          }
          break;
          
          
        case SDL_KEYUP: 
          {            
            if (e.key.keysym.sym == SDLK_z 
                || e.key.keysym.sym == SDLK_UP) {
              KEY_UP_PRESSED = false;
            } 
            if (e.key.keysym.sym == SDLK_s 
                       || e.key.keysym.sym == SDLK_DOWN) {
              KEY_DOWN_PRESSED = false;             
            }
            if (e.key.keysym.sym == SDLK_q 
                       || e.key.keysym.sym == SDLK_LEFT) {
              KEY_LEFT_PRESSED = false;             
            }
            if (e.key.keysym.sym == SDLK_d 
                       || e.key.keysym.sym == SDLK_RIGHT) {
              KEY_RIGHT_PRESSED = false;            
            }
          }
          break;
          
          
        case SDL_MOUSEMOTION: 
          {
            float speed = 0.5f;
            std::cout << "Mouse move: ";
            std::cout << e.motion.xrel << " | " << e.motion.yrel << std::endl;
            if ( e.motion.xrel != 0 ) {
              camera.rotateFront( float(-e.motion.xrel) * speed);
            }
            if ( e.motion.yrel != 0 ) {
              camera.rotateLeft( float(e.motion.yrel) * speed);
            }
            
          }
          break;

        default:
            break;
      }
    }

    /* CONTROL */
    
    float speed = 0.1f;      
    if (KEY_UP_PRESSED) {
      camera.moveFront(speed);
    } 
    else if (KEY_DOWN_PRESSED) {
      camera.moveFront(-speed);              
    }
    else if (KEY_LEFT_PRESSED) {
      KEY_LEFT_PRESSED = true;
      camera.moveLeft(speed);              
    }
    else if (KEY_RIGHT_PRESSED) {
      KEY_RIGHT_PRESSED = true;
      camera.moveLeft(-speed);              
    }
    
    
    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);
    
    /* Calcul de la camera */
    //globalMVMatrix = camera.getViewMatrix();
    globalMVMatrix = camera.getViewMatrix();
    

    /* 9_ Envoi des matrices au GPU */
    /* DESSIN DE LA TERRE */
    earthProgram.m_Program.use();
    
    glUniform1i(earthProgram.uEarthTexture, 0);
    glUniform1i(earthProgram.uCloudTexture, 1);
        
    glm::mat4 earthMVMatrix = glm::rotate( globalMVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
    
    glUniformMatrix4fv(
      earthProgram.uMVMatrix, // Location
      1, // Count
      GL_FALSE, // Transpose
      glm::value_ptr(earthMVMatrix)); // Value
    glUniformMatrix4fv(
      earthProgram.uNormalMatrix, // Location
      1, // Count
      GL_FALSE, // Transpose
      glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix)))); // Value
    glUniformMatrix4fv(
      earthProgram.uMVPMatrix, // Location
      1, // Count
      GL_FALSE, // Transpose
      glm::value_ptr(ProjMatrix * earthMVMatrix)); // Value
    
    /* 10_ Dessin de la TERRE */
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    
    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0); // On enlève les nuages
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    // 11_ Dessin des lunes
    moonProgram.m_Program.use();
    
    glUniform1i(moonProgram.uTexture, 0);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    
    glm::mat4 moonMVMatrix;
    for ( int i=0; i<32; i++) {
      /* 11_ Dessin d'une autre lune */      
      moonMVMatrix = glm::rotate(globalMVMatrix, windowManager.getTime(), rotationAxes[i]); // Translation * Rotation     
      moonMVMatrix = glm::translate(moonMVMatrix, translationValues[i]); // Translation * Rotation * Translation      
      moonMVMatrix = glm::scale(moonMVMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale 
      
      glUniformMatrix4fv(
        moonProgram.uMVMatrix, // Location
        1, // Count
        GL_FALSE, // Transpose
        glm::value_ptr(moonMVMatrix)); // Value
      glUniformMatrix4fv(
        moonProgram.uNormalMatrix, // Location
        1, // Count
        GL_FALSE, // Transpose
        glm::value_ptr(glm::transpose(glm::inverse(moonMVMatrix)))); // Value
      glUniformMatrix4fv(
        moonProgram.uMVPMatrix, // Location
        1, // Count
        GL_FALSE, // Transpose
        glm::value_ptr(ProjMatrix * moonMVMatrix)); // Value
      
      glDrawArrays(GL_TRIANGLES, 
                   0,
                   sphere.getVertexCount());
    }
    
    glActiveTexture(GL_TEXTURE0);
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
