#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

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
    GLfloat vertices[] = { -0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f };
    
    // Envoi
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    
    
    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    
    
    
    // Creaton d'un seul VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    
    // Bind
    glBindVertexArray(vao);
    
    // Activer
    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
        VERTEX_ATTR_POSITION, // index
        2, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized
        2*sizeof(GLfloat), // stride
        0 // pointer
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
