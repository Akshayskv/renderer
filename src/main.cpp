#include <iostream>
#include "window.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "shader.h"
#include "texture.h"

int main() {

    Window w {800, 600, "renderer"};
    try{
        Shader mysh("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
        VertexBuffer<TexturedVertex> buffer{{
            { 0.5f,  0.5f, 0.0f, 0.0f, 0.0f },   // top right
            { 0.5f, -0.5f, 0.0f,   1.0f, 0.0f },   // bottom right
            { -0.5f, -0.5f, 0.0f, 0.5f, 1.0f },   // bottom left 
        }};

        VertexArray varray;
        varray.addlayout<TexturedVertex>(buffer);
        Texture bricktex{"../assets/textures/wall.jpg"};
        mysh.bind();        
        bricktex.bind();

        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    
        while(w.isOpen()) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            varray.bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
            varray.unbind();
            w.update();
        }
        
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}