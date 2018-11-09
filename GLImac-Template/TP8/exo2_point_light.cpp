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
#include <glimac/TrackballCamera.hpp> 

using namespace glimac;

struct EarthProgram {
  Program m_Program;
  
  GLint uMVPMatrix;
  GLint uMVMatrix;
  GLint uNormalMatrix;
  GLint uEarthTexture;
  GLint uCloudTexture;
  GLint uKd;
  GLint uKs;
  GLint uShininess;
  GLint uLightPos_vs;
  GLint uLightIntensity;
  
  EarthProgram( const FilePath& applicationPath ) :
    m_Program(loadProgram(
      applicationPath.dirPath() + "shaders/3D.vs.glsl",
      applicationPath.dirPath() + "shaders/pointLightMulti.fs.glsl")) 
    {
      uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
      uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
      uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
      uEarthTexture = glGetUniformLocation(m_Program.getGLId(), "uEarthTexture");
      uCloudTexture = glGetUniformLocation(m_Program.getGLId(), "uCloudTexture");
      uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
      uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
      uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
      uLightPos_vs = glGetUniformLocation(m_Program.getGLId(), "uLightPos_vs");
      uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    }  
};

struct MoonProgram {
  Program m_Program;

  GLint uMVPMatrix;
  GLint uMVMatrix;
  GLint uNormalMatrix;
  GLint uTexture;
  GLint uKd;
  GLint uKs;
  GLint uShininess;
  GLint uLightPos_vs;
  GLint uLightIntensity;

  MoonProgram( const FilePath& applicationPath ):
        m_Program(loadProgram(
          applicationPath.dirPath() + "shaders/3D.vs.glsl",
          applicationPath.dirPath() + "shaders/pointLight.fs.glsl")) 
  {
    uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
    uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
    uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
    uShininess = glGetUniformLocation(m_Program.getGLId(), "uShininess");
    uLightPos_vs = glGetUniformLocation(m_Program.getGLId(), "uLightPos_vs");
    uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
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
  glm::mat4 ProjMatrix, MVMatrix, NormalMatrix, globalVMatrix;
  ProjMatrix = glm::perspective(glm::radians(70.0f), // Angle vertical de vue
                   (float) (WINDOW_WIDTH / WINDOW_HEIGTH), // Ratio de la fenetre
                   0.1f, // Near
                   100.f); // Far
  
  /* Création de la camera */
  TrackballCamera camera;  
  
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

          /* Touche clavier */
        case SDL_KEYDOWN: 
          {            
            float zoom = 1.0f;
            if (e.key.keysym.sym == SDLK_z 
                || e.key.keysym.sym == SDLK_UP) {
              std::cout << "Z or UP pressed" << std::endl;
              camera.moveFront(zoom);
            } 
            else if (e.key.keysym.sym == SDLK_s 
                       || e.key.keysym.sym == SDLK_DOWN) {
              std::cout << "S or DOWN pressed" << std::endl;
              camera.moveFront(-zoom);              
            }
          }
          break;
          
          
        case SDL_MOUSEMOTION: 
          {
            float speed = 1.0f;
            //std::cout << "Mouse move: ";
            //std::cout << e.motion.xrel << " | " << e.motion.yrel << std::endl;
            if ( e.motion.xrel != 0 ) {
              camera.rotateRight( float(e.motion.xrel) * speed);
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

    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao);
    
    /* Calcul de la camera */
    globalVMatrix = camera.getViewMatrix();
    
    /* Calcul de la lumiere */
    glm::vec4 pointLight(4.0f, 3.0f, 6.0f, 1.0f);
    glm::vec4 pLight4 = pointLight * globalVMatrix;
    glm::vec3 pLight = glm::vec3(pLight4.x, pLight4.y, pLight4.z);
    

    /* 9_ Envoi des matrices au GPU */
    /* DESSIN DE LA TERRE */
    earthProgram.m_Program.use();
        
    glm::mat4 earthMVMatrix = glm::rotate(globalVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0));
    
    glUniform1i(earthProgram.uEarthTexture, 0);
    glUniform1i(earthProgram.uCloudTexture, 1);
    // On envoi les variables uniformes
    // Shininess
    glUniform1f(earthProgram.uShininess, 50.0f);
    // uKd
    glUniform3fv(earthProgram.uKd,1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));
    // uKs
    glUniform3fv(earthProgram.uKs,1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.4f)));
    // uLightPos_vs
    glUniform3fv(earthProgram.uLightPos_vs, 1, glm::value_ptr(pLight));
    // uLightIntensity
    float earthLi = 5.f;
    glUniform3fv(earthProgram.uLightIntensity,1, glm::value_ptr(glm::vec3(earthLi, earthLi, earthLi))); 
    
    // MV
    glUniformMatrix4fv(
      earthProgram.uMVMatrix, // Location
      1, // Count
      GL_FALSE, // Transpose
      glm::value_ptr(earthMVMatrix)); // Value
    // Normal
    glUniformMatrix4fv(
      earthProgram.uNormalMatrix, // Location
      1, // Count
      GL_FALSE, // Transpose
      glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix)))); // Value
    // PMV
    glUniformMatrix4fv(
      earthProgram.uMVPMatrix, // Location
      1, // Count
      GL_FALSE, // Transpose
      glm::value_ptr(ProjMatrix * earthMVMatrix)); // Value    
    
    /* 10_ Dessin de la TERRE */
    glActiveTexture(GL_TEXTURE0);   glBindTexture(GL_TEXTURE_2D, textures[0]);
    glActiveTexture(GL_TEXTURE1);   glBindTexture(GL_TEXTURE_2D, textures[2]);
    
    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
    
    // On enlève les nuages
    glActiveTexture(GL_TEXTURE1);   glBindTexture(GL_TEXTURE_2D, 0); 
    glActiveTexture(GL_TEXTURE0);   glBindTexture(GL_TEXTURE_2D, 0);
    
    
    
    
    
    // 11_ Dessin des lunes
    moonProgram.m_Program.use();
    
    
    // On envoi les variables uniformes
    // Texture ID
    glUniform1i(moonProgram.uTexture, 0);
    // Shininess
    glUniform1f(moonProgram.uShininess, 50.0f);
    // uKd
    glUniform3fv(moonProgram.uKd, 1, glm::value_ptr(glm::vec3(0.f, 0.1f, 0.8f)));
    // uKs
    glUniform3fv(moonProgram.uKs, 1, glm::value_ptr(glm::vec3(1.0f, 0.6f, 0.f)));    
    // uLightIntensity
    float moonLi = 5.f;
    glUniform3fv(moonProgram.uLightIntensity,1, glm::value_ptr(glm::vec3(moonLi, moonLi, moonLi)));    
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    
    glm::mat4 moonMVMatrix;
    
    for ( int i=0; i<32; i++) {   
      
      /* 11_ Dessin d'une autre lune */
      // Translation * Rotation
      moonMVMatrix = glm::rotate(globalVMatrix, windowManager.getTime(), rotationAxes[i]);
      // Translation * Rotation * Translation
      moonMVMatrix = glm::translate(moonMVMatrix, translationValues[i]);
      // Translation * Rotation * Translation * Scale
      moonMVMatrix = glm::scale(moonMVMatrix, glm::vec3(0.2, 0.2, 0.2));
      
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
      
      // uLightPos_vs
      glUniform3fv(moonProgram.uLightPos_vs, 1, glm::value_ptr(pLight));
      
      glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
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
