#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp> 
#include <glimac/FilePath.hpp> 

using namespace glimac;

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
        applicationPath.dirPath() + "shaders/" + argv[1],
        applicationPath.dirPath() + "shaders/" + argv[2]);
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
    
    // Remplir
    GLfloat vertices[] = { -0.5f, -0.5f, 1.f, 0.0f, 0.0f, // premier sommet
        0.5f, -0.5f, 0.f, 1.f, 0.f, // deuxième sommet
        0.0f, 0.5f, 0.f, 0.f, 1.f // troisième sommet
         };
    
    // Envoi
    glBufferData(GL_ARRAY_BUFFER, 15*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    
    
    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Creaton d'un seul VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    
    // Bind
    glBindVertexArray(vao);
    
    // Activation
    // 0 et 1 sont tirés des shaders
    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    const GLuint VERTEX_ATTR_COLOR = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
        VERTEX_ATTR_POSITION, // index
        2, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized
        5*sizeof(GLfloat), // stride
        (const GLvoid*) 0 // pointer
    );
    glVertexAttribPointer(
        VERTEX_ATTR_COLOR, // index
        3, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized
        5*sizeof(GLfloat), // stride
        (const GLvoid*) (2*sizeof(GLfloat)) // pointer
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
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        
        // Update the display
        windowManager.swapBuffers();
    }

    // Liberation des ressources
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    
    return EXIT_SUCCESS;
}
